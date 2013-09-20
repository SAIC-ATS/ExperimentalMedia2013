
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
  int timeUnit = 100;

  int dotDuration = timeUnit;
  int dashDuration = dotDuration*3;
  int letterSpaceDuration = dashDuration;
  int wordSpaceDuration = dashDuration*3;
  
  
 

 
  
  // Methods
  void dot() {
    digitalWrite(ledPin, HIGH);
    delay(dotDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
  }
  void dash() {
    digitalWrite(ledPin, HIGH);
    delay(dashDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
  }
  void letterSpace() {
    delay(letterSpaceDuration);
  }
  void wordSpace() {
    delay(wordSpaceDuration);
  }
  
  
// Letters
void A() {
  dot();
  dash();
  letterSpace();
}

void D() {
  dash();
  dot();
  dot();
  letterSpace();
}

void G() {
  dash();
  dash();
  dot();
  letterSpace();
}

void H() {
  dot();
  dot();
  dot();
  dot();
  letterSpace();
}

void O() {
  dash();
  dash();
  dash();
  letterSpace();
}

void R() {
  dot();
  dash();
  dot();
  letterSpace();
}

void T() {
  dash();
  letterSpace();
}

void U() {
  dot();
  dot();
  dash();
  letterSpace();
}

void W() {
  dot();
  dash();
  dash();
  letterSpace();
}





void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
W();
H();
A();
T();
wordSpace();
H();
A();
T();
H();
wordSpace();
G();
O();
D();
wordSpace();
W();
R();
O();
U();
G();
H();
T();

wordSpace();
wordSpace();
wordSpace();

}


