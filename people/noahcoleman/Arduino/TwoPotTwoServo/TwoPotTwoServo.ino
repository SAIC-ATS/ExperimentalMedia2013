// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

Servo myServo0;  
Servo myServo1; // create servo object to control a servo 

int potPin0 = 0;
int potPin1 = 1;// analog pin used to connect the potentiometer
int val0;    // variable to read the value from the analog pin 
int val1;

void setup() 
{ 
  myServo0.attach(9);  // attaches the servo on pin 9 to the servo object 
  myServo1.attach(10);
  Serial.begin(9600);
} 

void loop() 
{ 
  val0 = analogRead(potPin0);            // reads the value of the potentiometer (value between 0 and 1023) 
  val0 = map(val0, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myServo0.write(val0);                  // sets the servo position according to the scaled value 
  delay(10);                           // waits for the servo to get there 

  val1 = analogRead(potPin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val1 = map(val1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myServo1.write(val1);                  // sets the servo position according to the scaled value 
  delay(10); 

  Serial.println(analogRead(potPin1));
}



