const int potPin = A0;
const int potPin2 = A1;
const int BAUD_RATE = 9600;

void setup()
{
  Serial.begin(BAUD_RATE);
}

void loop()
{
  // Get the current pot value
  int pot1Value = analogRead(potPin);
  int pot2Value = analogRead(potPin2);
  
  Serial.print(pot1Value);
  Serial.print(",");
  Serial.println(pot2Value);
  
  // Delay
  delay(100);
}

