// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

Servo myServo0;  
Servo myServo1; // create servo object to control a servo 


int incomingStuff;     //  
int val1 = 0;          //variable for the servo position
String mouseDataIn;
String data[2];
int counter;

void setup() 
{ 
  myServo0.attach(9);  // attaches the servo on pin 9 to the servo object 
  myServo1.attach(10);
  Serial.begin(9600);
  counter = 0;
  mouseDataIn = String("");
} 

void loop() 
{ 
  if (Serial.available() > 0) {

    incomingStuff = Serial.read();
    if(incomingStuff >= '0' & incomingStuff <= '9'){
      mouseDataIn += incomingStuff;
    }
    if (incomingStuff == ','){  // Handle delimiter
      data[counter] = String(mouseDataIn);
      mouseDataIn = String("");
      counter = counter + 1;
    }
    if(incomingStuff == '\n'){
      unsigned int length = mouseDataIn.length();
      char storage[length];
      mouseDataIn.toCharArray(storage, length);
      val1 = atoi(storage);//atoi converts from char array to integ

      //val1 = int(mouseDataIn);
      mouseDataIn = String("");
      counter = 0;
    }
    //    Serial.print("mouseX: ");

  }


  myServo0.write(val1);                  // sets the servo position  
  delay(15);                           

  Serial.println(val1);


  //  val0 = analogRead(potPin0);            // reads the value of the potentiometer (value between 0 and 1023) 
  //  val0 = map(val0, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  //  myServo0.write(val0);                  // sets the servo position according to the scaled value 
  //  delay(15);                           // waits for the servo to get there 
  //
  //  val1 = analogRead(potPin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  //  val1 = map(val1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  //  myServo1.write(val1);                  // sets the servo position according to the scaled value 
  //  delay(15); 

  //Serial.println(analogRead(potPin1));
}




