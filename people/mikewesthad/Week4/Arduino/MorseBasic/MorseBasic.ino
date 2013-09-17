float dotLength;
float dashLength;
float letterSpaceLength;
float wordSpaceLength;

// What God Hath Wrought in morse code where ' ' is a space, '>' indicates a new letter and '|' indicates a new word
char morseString[] = ". - ->. . . .>. ->-|- - .>.  .>- . .|. . . .>. ->->. . . .|. - ->.  . .>.  .>. . ->- - .>. . . .>-";

int led = 13;

void setup() {
  
  // Explanation of American Morse Code from: http://w1tp.com/percode.htm
  //  Dot is basic unit of time
  //  Dash is three dits
  //  Space between dots and dashes within characters is one dot
  //  Space between letters is 3 dots
  //  Space between words is 7 dots
  
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
