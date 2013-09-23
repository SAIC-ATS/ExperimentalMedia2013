int ledPin = 11;      // LED connected to digital pin 11
int potPin = 0;   // potentiometer connected to analog pin 0
int val = 0;         // variable to store the read value

void setup()
{
  pinMode(ledPin, OUTPUT);   // sets the pin as output
  Serial.begin(9600);//begins serial communication
}

void loop()
{
  val = analogRead(potPin);   // read the input pin
  analogWrite(ledPin, val / 4);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  Serial.println(val);//tells the serial port to print the value of the pot
}

