
const int potPinA = A0;
const int potPinB = A1;

int value = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int potValue1 = analogRead(potPinA);
  int potValue2 = analogRead(potPinB);
  
  //Serial.println(value);
  
  value++;
  
  if(value > 255) value = 0;
  
  Serial.print(potValue1); 
  Serial.print(","); 
  Serial.println(potValue2);

  
  
  delay(100);
}


