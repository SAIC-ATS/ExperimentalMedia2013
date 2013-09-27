const int potPin = A0;
const int BAUD_RATE = 9600;

// Array variables for tracking a window of potentiometer values
//  We want to hold on to the last NUM_SAMPLES values and perform
//  an average on them to arrive at a 'current' value - this 
//  is called a moving average: http://en.wikipedia.org/wiki/Moving_average
//  NOTE: The larger NUM_SAMPLES, the smoother the values, but also
//  the longer it will take the average to move in response to you turning the
//  potentiometer
const int NUM_SAMPLES = 20;
int potSamples[NUM_SAMPLES];
int potIndex = 0;
int totalPotValue = 0;

// Change detection variables
//  Even with the averaging, our pot value will likely still flip between
//  neighboring values, so this changeThreshold is used in order to only
//  update the pot value sent out from the arduino if the pot value
//  has changed by a specified amount
int lastAveragePotValue = 0;
const int CHANGE_THRESHOLD = 3;

void setup()
{
  Serial.begin(BAUD_RATE);
  
  // Fill the array of samples with zeros
  for (int i=0; i<NUM_SAMPLES; i++) potSamples[i] = 0;     
}

void loop()
{
  // potSamples[potIndex] is the oldest data in the array
  // We are about to override it with a new value, but first
  // we need to subtract it from our running total of pot values  
  totalPotValue -= potSamples[potIndex];
  
  // Get the current pot value
  int currentPotValue = analogRead(potPin);
  
  // Update our running total and add the new value to the array
  totalPotValue += currentPotValue;
  potSamples[potIndex] = currentPotValue;
  
  // Increment our index
  potIndex++;
  if (potIndex>NUM_SAMPLES-1) potIndex = 0;
  
  // Calculate the average pot value
  int averagePotValue = totalPotValue / NUM_SAMPLES;
  
  // Detect whether the new average pot value has changed enough
  // from our last saved average pot value
  int change = abs(averagePotValue-lastAveragePotValue);
  if (change >= CHANGE_THRESHOLD){
    lastAveragePotValue = averagePotValue;
  }
  
  // Output the last saved average pot value 
  // i.e. the last one that exceeeded the change threshold
  Serial.println(lastAveragePotValue);
  
  // Delay
  delay(10);
}

