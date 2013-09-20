/* 
"What hath God wrought" in morse code
A · —
D — · ·
G — — ·
H · · · ·
O . space .
R · space · ·
T —
U · · —
W · — —
*/

// defining ledPin on pin no.13
const int ledPin = 13;


// Duration of blinks and pauses
int dah = 300;
int dit = 70;
int space = 50;
int letterSpace = 100;
int wordSpace = 600;

// setting pin 13 as output
void setup() {
  pinMode(ledPin, OUTPUT);
}


void loop() {
  
// Word WHAT ---------------------------------------------------------------

  // letter "W" = .--
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // letter space
  delay(letterSpace);
  
  // letter H = ....
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // letter space
  delay(letterSpace);
  
 // letter A = .-
    digitalWrite(ledPin, HIGH);
    delay(dit);
    digitalWrite(ledPin, LOW);
    delay(space);
  
    digitalWrite(ledPin, HIGH);
    delay(dah);
    digitalWrite(ledPin, LOW);
    delay(space);
  
  // letter space
  delay(letterSpace);
  
  // letter T = -
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // word HATH --------------------------------------------------------------
  delay(wordSpace);
  
  // letter H = ....
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // letter space
  delay(letterSpace);
  
  // letter A = .-
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);

  // letter space
  delay(letterSpace);
  
  // letter T = -
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // letter space
  delay(letterSpace);
  
  // letter H = ....
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // word GOD --------------------------------------------------------------
  delay(wordSpace);
  
  // letter G = --.
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);
  
  // letter O = . .
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);
  
  // letter D = -..
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
    
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
    
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // word WROUGHT --------------------------------------------------------------
  delay(wordSpace);
  
  // letter "W" = .--
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  // letter space
  delay(letterSpace);
  
  // letter R = . ..
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);

  delay(space);

  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);

  // letter O = . .
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);
  
  // letter U = ..-
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);

  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);

  // letter G = --.
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);
  
  // letter H = ....
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
  digitalWrite(ledPin, HIGH);
  delay(dit);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// letter space
  delay(letterSpace);
  
  // letter T = -
  digitalWrite(ledPin, HIGH);
  delay(dah);
  digitalWrite(ledPin, LOW);
  delay(space);
  
// pause before repeat
delay(wordSpace);
delay(wordSpace);
delay(wordSpace);
  
  }
  
