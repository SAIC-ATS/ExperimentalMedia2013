const int ledPin = 13; //const makes a variable read-only
const int smallLed = 7;
//char is an integral type variable, like "a"
//unsigned means you can't have negative, but you get more positive memory


void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(smallLed, OUTPUT);
  
}

void loop(){
  digitalWrite(ledPin, HIGH);
  //delay(1000); //delay stops everything completely
  digitalWrite(ledPin, LOW);
  //delay (1000);
  
  digitalWrite(smallLed, HIGH);
  //delay(1000);
  digitalWrite(smallLed, LOW);
  //delay (1000);
  
  
}
