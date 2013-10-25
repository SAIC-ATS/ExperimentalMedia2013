#include <Servo.h>
Servo servoX;
Servo servoY;
const int laserPin = 11;
const int potPin = A0;

int servoXMin = 70;// min range for servoX
int servoXMax = 120;// max range for servoX
int laserState = LOW;

long wavelength = 0;// sets delay for x axis (wavelength)
int interval = 2;


void setup()
{  
  Serial.begin(9600);
  servoX.attach(9);
  servoY.attach(10);
  pinMode(laserPin, OUTPUT);
  pinMode(potPin, INPUT);

//  //Calibrate X Axis
//  int i=0;
//  while(i<3){
//    digitalWrite(laserPin, HIGH);
//    servoX.write(servoXMin);
//    servoY.write(90);
//    delay(500);
//    servoX.write(servoXMax);
//    servoY.write(90);
//    delay(500);
//    i++;
//  }//while loop
}

void loop()
{

  int potValue = analogRead(potPin);
  wavelength = map(potValue, 0, 1023, 10, 100);
  //Serial.println(potValue);
  //Serial.println(wavelength);


  unsigned long currentMillis = millis(); //get current time
  unsigned long previousMillis = 0;
  
for(int time = 0; time < 2; time++){
      digitalWrite(laserPin, HIGH);
      for(float i = servoXMin;i < servoXMax;i++){
        delay(wavelength);
        servoX.write(i);
        servoY.write(sin(i)*10 +90);
      }//end of for loop 1

      for(float i = servoXMax; i> servoXMin; i--){
        delay(wavelength);
        servoX.write(i);
        servoY.write(sin(i+10)*10 +90);
      }//end of for loop 2
      newTime++;
Serial.println(time);
}

for(int timer = 0; timer < 2; timer++){
 digitalWrite(laserPin, LOW);
 servoX.write(servoXMin);
 servoY.write(90);
}//end of off for loop





  //    for(float i = servoXMin;i < servoXMax;i++){
  //    delay(wavelength);
  //    servoX.write(i);
  //    servoY.write(tan(i+10)*10 +90);
  //  }//end of for loop 3a
  //
  //  for(float i = servoXMax; i> servoXMin; i--){
  //    delay(wavelength);
  //    servoX.write(i);
  //    servoY.write(tan(i)*10 +90);
  //  }//end of for loop 2a

  //  digitalWrite(laserPin, LOW);


}//end loop
















