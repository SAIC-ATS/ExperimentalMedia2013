// Explanation of International Morse Code from: http://en.wikipedia.org/wiki/Morse_code
//  Dot is basic unit of time
//  Dash is three dits
//  Space between dots and dashes within characters is one dot
//  Space between letters is 3 dots
//  Space between words is 7 dots 

 
// These units are in seconds
#define DOT_LENGTH 0.25;
float dotLength = DOT_LENGTH;      
float dashLength = 3 * DOT_LENGTH;  

String message = "What Hath God Wrought What Hath God Wrought What Hath God Wrought";


int led = 13;


void setup() {
  pinMode(led, OUTPUT);
  
  // Loop through each letter of the message
  for (int i=0; i<message.length(); i++) {
    
    // Get the current character
    char c = message[i];
    
    // Convert it to morse 
    String morseString = internationalMorse(c);
    
    // Process the morse string to the LED
    processMorseToLED(morseString);
    
    // Hacky solution to the problem of determining when to signal a space between letters
    //   If the current character is not a space AND
    //   If there is another character left in the string AND
    //   The next character is not a space
    //      Then send a signal to indicate a space between letters
    if ((i+1<message.length()) && (message[i]!=' ') && (message[i+1]!=' ')) {
        processMorseToLED("   "); // Space between letters is equal to three dots
    }
  }
  
  // Turn off LED after end of message
  digitalWrite(led, LOW);
}

void processMorseToLED(String morse) {
  for (int i=0; i<morse.length(); i++) {
    char c = morse[i];
    if (c == '.') {   
      digitalWrite(led, HIGH);
      delay(dotLength * 1000.0);
    }
    else if (c == '-') {   
      digitalWrite(led, HIGH);
      delay(dashLength * 1000.0);
    }
    else if (c == ' ') {   
      digitalWrite(led, LOW);
      delay(dotLength * 1000.0);
    }
  }
  
}

// Given a char, c, return the uppercase version (if c is alphabetical)
//   Lower Case Letters a-z are from 97 to 122
//   Upper Case Letters are from 65 to 90
//   Converting to upper case then just requires subtacting 32
char convertCharToUpper(char c) {
  if (c >= 97 && c <= 122) c -= 32;  
  return c;
}

// Given an alphanumeric char (or space), c, return a string of morse code where:
//  a dot is represented by '.'
//  a dash is represented by '-'
//  the gap between dots and dashes is represented by ' '
//  a space between words is represented by '       '
// NOTE: all other chars will return an empty string
String internationalMorse(char c) {
  c = convertCharToUpper(c);
  if (c == 'A')      return ". -";
  else if (c == 'B') return "- . . .";
  else if (c == 'C') return "- . - .";
  else if (c == 'D') return "- . .";
  else if (c == 'E') return ".";
  else if (c == 'F') return ". . - .";
  else if (c == 'G') return "- - .";
  else if (c == 'H') return ". . . .";
  else if (c == 'I') return ". .";
  else if (c == 'J') return ". - - -";
  else if (c == 'K') return "- . -";
  else if (c == 'L') return ". - . .";
  else if (c == 'M') return "- -";
  else if (c == 'N') return "- .";
  else if (c == 'O') return "- - -";
  else if (c == 'P') return ". - - .";
  else if (c == 'Q') return "- - . -";
  else if (c == 'R') return ". - .";
  else if (c == 'S') return ". . .";
  else if (c == 'T') return "-";
  else if (c == 'U') return ". . -";
  else if (c == 'V') return ". . . -";
  else if (c == 'W') return ". - -";
  else if (c == 'X') return "- . . -";
  else if (c == 'Y') return "- . - -";
  else if (c == 'Z') return "- - . .";
  else if (c == '1') return ". - - - -";
  else if (c == '2') return ". . - - -";
  else if (c == '3') return ". . . - -";
  else if (c == '4') return ". . . . -";
  else if (c == '5') return ". . . . .";
  else if (c == '6') return "- . . . .";
  else if (c == '7') return "- - . . .";
  else if (c == '8') return "- - - . .";
  else if (c == '9') return "- - - - .";
  else if (c == '0') return "- - - - -";
  else if (c == ' ') return "       ";
  else               return "";
}

void loop() {
  // No need to loop
}


