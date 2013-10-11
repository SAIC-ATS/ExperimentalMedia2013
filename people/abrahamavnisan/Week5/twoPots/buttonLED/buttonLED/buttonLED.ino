const int button2 = 2;
const int button3 = 3;
const int button4 = 4;

const int led9 = 9;
const int led10 = 10;
const int led11 = 11;

int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

void setup()
{
  Serial.begin(9600);
  
//  digitalWrite(button2, HIGH);
//  digitalWrite(button3, HIGH);
//  digitalWrite(button4, HIGH);  
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(led9,OUTPUT);
  pinMode(led10,OUTPUT);
  pinMode(led11,OUTPUT);
  
  
}

void loop() 
{
   int buttonState2 = digitalRead(button2);
   int buttonState3 = digitalRead(button3);
   int buttonState4 = digitalRead(button4);
   Serial.println(buttonState2);
   Serial.println(buttonState3);
   Serial.println(buttonState4);
   
   digitalWrite(led9,!digitalRead(button2));
   digitalWrite(led10,!digitalRead(button3));
   digitalWrite(led11,!digitalRead(button4));
   
   delay(1);
   
  
}
