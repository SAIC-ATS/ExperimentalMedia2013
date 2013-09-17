float dotLength;
float dashLength;
float letterSpaceLength;
float wordSpaceLength;

char morseString[] = ". - ->. . . .>. ->-|- - .>.  .>- . .|. . . .>. ->->. . . .|. - ->.  . .>.  .>. . ->- - .>. . . .>-";

int led = 13;

void setup() {
  dotLength = 0.25;
  dashLength = 3 * dotLength;
  letterSpaceLength = 3 * dotLength;
  wordSpaceLength = 7 * dotLength;
  
  pinMode(led, OUTPUT);    
  
  int numberChar = sizeof(morseString) / sizeof(char);
  for (int i = 0; i < numberChar; i++) {
    char currentChar = morseString[i]; 
    if (currentChar == '.') {   
      digitalWrite(led, HIGH);
      delay(dotLength * 1000.0);
    }
    else if (currentChar == '-') {   
      digitalWrite(led, HIGH);
      delay(dashLength * 1000.0);
    }
    else if (currentChar == ' ') {   
      digitalWrite(led, LOW);
      delay(dotLength * 1000.0);
    }
    else if (currentChar == '>') {   
      digitalWrite(led, LOW);
      delay(letterSpaceLength * 1000.0);
    }
    else if (currentChar == '|') {   
      digitalWrite(led, LOW);
      delay(wordSpaceLength * 1000.0);
    }
  }
}

void loop() {
 

 
  
}
