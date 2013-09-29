const int potPin = A0;
const int BAUD_RATE = 9600;

// Array variables for tracking a window of potentiometer values
//  Use this array to calculate a moving average and variance
//    http://en.wikipedia.org/wiki/Moving_average
//    http://en.wikipedia.org/wiki/Deviation_(statistics)

const int NUM_SAMPLES = 10;
float potSamples[NUM_SAMPLES];
int potIndex = 0;
float totalPotValue = 0;


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
  float currentPotValue = analogRead(potPin);
  
  // Update our running total and add the new value to the array
  totalPotValue += currentPotValue;
  potSamples[potIndex] = currentPotValue;
  
  // Increment our index
  potIndex++;
  if (potIndex>NUM_SAMPLES-1) potIndex = 0;
  
  // Calculate the average pot value
  float averagePotValue = totalPotValue / NUM_SAMPLES;

  float average_deviation = 0.0;
  for (int i=0; i<NUM_SAMPLES; i++) { 
    average_deviation += abs(currentPotValue - averagePotValue);
  }
  average_deviation /= NUM_SAMPLES;
  
  
  // Output the last saved average pot value 
  // i.e. the last one that exceeeded the change threshold
  Serial.print(currentPotValue);
  Serial.print(", ");
  Serial.print(averagePotValue);
  Serial.print(", ");
  Serial.println(average_deviation);
  
  // Delay
  delay(100);
}

