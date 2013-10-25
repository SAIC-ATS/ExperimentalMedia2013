const int ledGreenPin = 9;
const int ledYellowPin = 10;
const int ledRedPin = 11;

const int buttonPinA = 2;
const int buttonPinB = 3;
const int buttonPinC = 4; 

int buttonStateGreen = 0;
int buttonStateYellow = 0;
int buttonStateRed = 0;

void setup(){
pinMode (ledGreenPin, OUTPUT);
pinMode (ledYellowPin, OUTPUT);
pinMode (ledRedPin, OUTPUT);

pinMode (buttonPinA, INPUT_PULLUP);
pinMode (buttonPinB, INPUT_PULLUP);
pinMode (buttonPinC, INPUT_PULLUP);

}


void loop(){
//  digitalWrite(ledGreenPin, !digitalRead(buttonPinA)
  
  
  
buttonStateGreen = digitalRead(buttonPinA);
if (buttonStateGreen == !HIGH) {
  digitalWrite(ledGreenPin, HIGH);
}
else{
  digitalWrite(ledGreenPin, LOW);
}

buttonStateYellow = digitalRead(buttonPinB);
if (buttonStateYellow == LOW) {
  digitalWrite(ledYellowPin, HIGH);
}
else{
  digitalWrite(ledYellowPin, LOW);
}

buttonStateRed = digitalRead(buttonPinC);
if (buttonStateRed == LOW) {
  digitalWrite(ledRedPin, HIGH);
}
else{
  digitalWrite(ledRedPin, LOW);
}



}

