
const int potPinA = A0;
//const int potPinB = A1;

int value = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int potValue1 = analogRead(potPinA);
//  int potValue2 = analogRead(potPinB);
  
  //Serial.println(value);
  
  value++;
  
  if(value > 255) value = 0;
  
  Serial.println(potValue1); //make sure to make it "print" when adding 2nd pot
//  Serial.print(","); 
//  Serial.println(potValue2);

  
  
  delay(100);
}


