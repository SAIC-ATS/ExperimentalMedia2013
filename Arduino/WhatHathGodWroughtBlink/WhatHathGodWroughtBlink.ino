const int ledPin = 13;
int dot = 100;
int dash = dot*3;
int letterSpace = dash;
int wordSpace = dash*3+1;
int dotSpace = dot;


void setup(){
  
  pinMode (ledPin, OUTPUT);
}

void loop(){
  Dit();//W
  Dah();
  Dah();
  LetterSpace();
  Dit();//H
  Dit();
  Dit();
  Dit();
  LetterSpace();
  Dit();//A
  Dah();
  LetterSpace();
  Dah();//T
  WordSpace();
  Dit();//H
  Dit();
  Dit();
  Dit();
  LetterSpace();
  Dit();//A
  Dah();
  LetterSpace();
  Dah();//T
  LetterSpace();
  Dit();//H
  Dit();
  Dit();
  Dit();
  WordSpace();
  Dah();//G
  Dah();
  Dit();
  LetterSpace();
  Dah();//O
  Dah();
  Dah();
  LetterSpace();
  Dah();//D
  Dit();
  Dit();
  WordSpace();
  Dit();//W
  Dah();
  Dah();
  LetterSpace();
  Dit();//R
  Dah();
  Dit();
  LetterSpace();
  Dah();//O
  Dah();
  Dah();
  LetterSpace();
  Dit();//U
  Dit();
  Dah();
  LetterSpace();
  Dah();//G
  Dah();
  Dit();
  LetterSpace();
  Dit();//H
  Dit();
  Dit();
  Dit();
  LetterSpace();
  Dah();//T
  LetterSpace();
  Dit();//?
  Dit();
  Dah();
  Dah();
  Dit();
  Dit();
  WordSpace();
}


//Functions

//Dit
void Dit(){
  digitalWrite(ledPin, HIGH);
  delay(dot);
  digitalWrite(ledPin, LOW);
  delay(dotSpace);
}
//Dah
void Dah(){
  digitalWrite(ledPin, HIGH);
  delay(dash);
  digitalWrite(ledPin, LOW);
  delay(dotSpace);
}
//Space between words
void WordSpace(){
  digitalWrite(ledPin, LOW);
  delay(wordSpace);
}
//Space between letters
void LetterSpace(){
  digitalWrite(ledPin, LOW);
  delay(letterSpace);
}
