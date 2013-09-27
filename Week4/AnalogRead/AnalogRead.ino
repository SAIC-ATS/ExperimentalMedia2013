
const int potPin = A0;

int value = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //int potValue = analogRead(potPin);
  
  Serial.println(value);
  
  value++;
  
  if(value > 255) value = 0;
  
//  Serial.println(potValue);
  
  delay(100);
}

