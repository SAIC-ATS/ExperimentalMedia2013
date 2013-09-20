
int ledPin = 13; // LED connected to pin 13

// What hath God wrought
void setup() {// run once, when the sketch starts
    pinMode(ledPin, OUTPUT); // sets the pin as output
}
 
void loop() { // run over and over again
 dits();
 dashs();
 dashs();
delay(200);
dits();
dits();
dits();
dits();
delay(200);
dits();
dashs();
delay(200);
dashs();
delay(400);


dits();
dits();
dits();
dits();
delay(200);
dits();
dashs();
delay(200);
dashs();
delay(200);
dits();
dits();
dits();
dits();
delay(400);

dashs();
dashs();
dits();
delay(200);
dashs();
dashs();
dashs();
delay(200);
dashs();
dits();
dits();
delay(400);

dits();
dashs();
dashs();
delay(200);
dits();
dashs();
dits();
delay(200);
dashs();
dashs();
dashs();
delay(200);
dits();
dits();
dashs();
delay(200);
dashs();
dashs();
dits();
delay(200);
dits();
dits();
dits();
dits();
delay(200);
dashs();
delay(200);

delay(4000);




}
 

void dits (){
  
  digitalWrite(ledPin,HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
  delay(100);
}

void dashs(){
  
  digitalWrite(ledPin,HIGH);
  delay(300);
  digitalWrite(ledPin,LOW);
  delay(100);
  
}
