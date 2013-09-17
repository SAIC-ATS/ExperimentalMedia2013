/*
  Morse Advanced
  Input any phrase, translate it to International Morse code (American is obsolete 
  so I figured I'd just go with International), and output to LED. My Morse Code
  reference:  http://en.wikipedia.org/wiki/Morse_code
 */
 
// Set time unit, dit and dah... (in mS)
int time_unit = 150; //don't really need this but it's a bit more elegant this way I think
int dit = time_unit;
int dah = time_unit*3;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name) {
int led = 13;

// Set Phrase to 'translate'
// only use all caps and no punctuation (because I'm lazy);
char myPhrase[ ] = "WHAT HATH GOD WROUGHT";
//int loopA; // counters for the various loops
//int loopB;
//int loopC;
int repeat_dot; // counters for dot and dash repetitions
int repeat_dash;
char x; // this stores the *next* character in the string, to determine how long of a gap

void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(led, OUTPUT);       
}

void loop() {
    Serial.print("TOP OF LOOP \n");
    int loopA = 0;
    while (loopA < sizeof(myPhrase)+1) {
      Serial.println("Loop number "); // All serial.print functions are for debugging in the serial monitor
      Serial.print(loopA);
      Serial.print("\n Character in this loop: ");
      Serial.print(myPhrase[loopA]);
      if (myPhrase[loopA]!=' ') { // So that functions morse and gap to run for spaces between words
      morse(myPhrase[loopA]);
      gap(myPhrase[loopA+1]);
      }
      loopA++;
    } 
}

void dot(int repeat_dot) {
  for (int loopB = 0; loopB < repeat_dot; loopB++) {
    Serial.println("dot");
    digitalWrite(led, HIGH);
    delay(dit);
    digitalWrite(led,LOW);
    delay(dit);
  }
}

void dash(int repeat_dash) {
  for (int loopC = 0; loopC < repeat_dash; loopC++) {
    Serial.println("dash");
    digitalWrite(led,HIGH);
    delay(dah);
    digitalWrite(led,LOW);
    delay(dit);
    }
}

void gap(char x) {
       Serial.println("function gap called");
 if (x==' ') {
     delay(time_unit*6); // six not seven because one time_unit delay is built into the dash and dot functions
     Serial.println("delay seven");
     }
     else if (x=='\0') { // delay for end of phrase
       delay(time_unit*9);
       Serial.println("delay nine");
     }
     else {
        Serial.println("delay three");
        delay(time_unit*2); //only two since one time_unit delay is built in to the dash and dot functions
     }
}
      
void morse(char x) {
  Serial.println("\n function morse called");
  if (x=='A') {
      dot(1);
      dash(1);
      }
    else if (x=='B') {
      dash(1);
      dot(3);
      }
    else if (x=='C') {
      dash(1);
      dot(1);
      dash(1);
      dot(1);
      }
    else if (x=='D') {
      dash(1);
      dot(2);
      }
    else if (x=='E') {
      dot(1);
      }
    else if (x=='F') {
      dot(2);
      dash(1);
      dot(1);
      }
    else if (x=='G') {
      dash(2);
      dot(1);
      }
    else if (x=='H') {
      dot(4);
      }
    else if (x=='I') {
      dot(2);
      }
    else if (x=='J') {
      dot(1);
      dash(3);
      }
    else if (x=='K') {
      dash(1);
      dot(1);
      dash(1);
      }
    else if (x=='L') {
      dot(1);
      dash(1);
      dot(2);
      }
    else if (x=='M') {
      dash(2);
      }
    else if (x=='N') {
      dash(1);
      dot(1);
      }
    else if (x=='O') {
      dash(3);
      }
    else if (x=='P') {
      dot(1);
      dash(2);
      dot(1);
      }
    else if (x=='Q') {
      dash(2);
      dot(1);
      dash(1);
      }
    else if (x=='R') {
      dot(1);
      dash(1);
      dot(1);
      }
    else if (x=='S') {
      dot(3);
      }
    else if (x=='T') {
      dash(1);
      }
    else if (x=='U') {
      dot(2);
      dash(1);
      }
    else if (x=='V') {
      dot(3);
      dash(1);
      }
    else if (x=='W') {
      dot(1);
      dash(2);
      }
    else if (x=='X') {
      dash(1);
      dot(2);
      dash(1);
      }
    else if (x=='Y') {
      dash(1);
      dot(1);
      dash(2);
      }
    else if (x=='Z') {
      dash(2);
      dot(2);
      }
   }
