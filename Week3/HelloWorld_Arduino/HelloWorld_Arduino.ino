// This is a comment
// This is another comment.

const int ledPin = 13;		// set our pin to 13
const int delayOne = 1000;  // set our first delay variable to 1000 milliseconds (ms)
const int delayTwo = 500;   // set our second delay variable to 500 ms

// the setup function gets called once when the Arduino is powered on or reset
void setup() 
{
  pinMode(ledPin,OUTPUT);  // we must tell the Arduino if we want the pin to be an input pin or an output pin. 
}

// the loop function is called repeatedly as fast as possible
void loop()
{
  digitalWrite(ledPin,HIGH); // this function tells ledPin (13 above) to go "HIGH" meaning that a small voltage is applied.
  delay(delayOne); // this tells the void loop() function to STOP and wait for 1000 ms
  digitalWrite(ledPin,LOW);  // this function tells ledPin (13 above) to go "LOW" meaning that zero voltage is applied (ground).
  delay(delayTwo); // this tells the void loop() function to STOP and wait for 500 ms

  // when we reach the end of the loop, it goes to the top of the loop and starts over again with digitalWrite(ledPin,HIGH);
}
