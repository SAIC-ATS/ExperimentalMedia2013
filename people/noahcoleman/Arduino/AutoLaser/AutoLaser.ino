#include <Servo.h>
Servo servoX;
Servo servoY;
const int laserPin = 11;
const int potPin = A1;

int laserState = LOW;

int servoXMin = 70;// min range for servoX
int servoXMax = 120;// max range for servoX
//int wavelength = 40;// sets delay for x axis (wavelength)

long previousMillis = 0;
long wavelength = 40;


void setup()
{  
  Serial.begin(9600);
  servoX.attach(9);
  servoY.attach(10);
  pinMode(laserPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop()
{


  //  int potValue = analogRead(potPin);
  //  Serial.println(potValue);
  unsigned long currentMillis = millis(); //get current time

  digitalWrite(laserPin, HIGH);
  for(float i = servoXMin;i < servoXMax;i++){
    if(currentMillis - previousMillis > wavelength) {
//      Serial.println(currentMillis - previousMillis);
      servoX.write(i);
      servoY.write(sin(i)*5 +90);
      previousMillis = currentMillis;
//      Serial.println(currentMillis);
    }//end if  
  }//end of for loop
  
  for(float i = servoXMax; i> servoXMin; i--){
         if(currentMillis - previousMillis > wavelength) {
//      Serial.println(currentMillis - previousMillis);
      servoX.write(i);
      servoY.write(sin(i)*5 +90);
      previousMillis = currentMillis;
//      Serial.println(currentMillis);
    }//end if  
  }//end of for loop 2
  //  digitalWrite(laserPin, LOW);
}//end loop












