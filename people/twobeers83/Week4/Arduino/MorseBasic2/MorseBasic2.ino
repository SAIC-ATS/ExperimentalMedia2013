
/* 
"What hath God wrought" in morse code
A · —
D — · ·
G — — ·
H · · · ·
O ---
R .-.
T —
U · · —
W · — —
*/


  // Variables

  int ledPin = 13;
  int potPin = A0;
  int potValue;
  int timeUnit;
  
  char myPhrase[ ] = "WHAT HATH GOD WROUGHT";


  int dotDuration = timeUnit;
  int dashDuration = dotDuration*3;
  int letterSpaceDuration = dashDuration;
  int wordSpaceDuration = dashDuration*3;

  
  
 
void update() {
  int potValue = analogRead(potPin);
  timeUnit = potValue;
  Serial.println(potValue);
}
  
  void dot() {
    digitalWrite(ledPin, HIGH);
    delay(dotDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
    update(); 
  }
  
  void dash() {
    digitalWrite(ledPin, HIGH);
    delay(dashDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
    update();
  }
  
  void letterSpace() {
    delay(letterSpaceDuration);
    update();
  }
  
  void wordSpace() {
    delay(wordSpaceDuration);
    update();
  }
  


void morse(char x) {
  if (x=='A') {
  dot();
  dash();
  letterSpace();
  }
  else if (x=='D') {
  dash();
  dot();
  dot();
  letterSpace();
  }
  else if (x=='G') {
  dash();
  dash();
  dot();
  letterSpace();
  }
  else if (x=='H') {
  dot();
  dot();
  dot();
  dot();
  letterSpace();
  }
  else if (x=='O') {
  dash();
  dash();
  dash();
  letterSpace();
  }
  else if (x=='R') {
  dot();
  dash();
  dot();
  letterSpace();
  }
  else if (x=='T') {
  dash();
  letterSpace();
  }
  else if (x=='U') {
  dot();
  dot();
  dash();
  letterSpace();
  }
  else if (x=='W') {
  dot();
  dash();
  dash();
  letterSpace();
  }
}





void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  
morse(myPhrase);

int potValue = analogRead(potPin);
Serial.println(potValue);

wordSpace();
wordSpace();
wordSpace();

}


