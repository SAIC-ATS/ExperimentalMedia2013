const int ledPin0 = 9;
const int ledPin1 = 10;
const int ledPin2 = 11;
const int buttonPin0 = 2;
const int buttonPin1 = 3;
const int buttonPin2 = 4;

void setup()
{
  // Set pin modes
  pinMode(ledPin0,OUTPUT);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(buttonPin0,INPUT_PULLUP);
  pinMode(buttonPin1,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
}

void loop()
{
  // you can do it this way ifyou need the button
  // value for something else.
  int buttonValue0 = !digitalRead(buttonPin0);  
  digitalWrite(ledPin0,buttonValue0);
  
  // or you can just set it directly if you don't
  // need the button value for other purposes.
  digitalWrite(ledPin1,!digitalRead(buttonPin1));
  digitalWrite(ledPin2,!digitalRead(buttonPin2));
}
