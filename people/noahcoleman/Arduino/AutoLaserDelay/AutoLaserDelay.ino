#include <Servo.h>
Servo servoX;
Servo servoY;
const int laserPin = 11;
const int potPin = A0;

int servoXMin = 70;// min range for servoX
int servoXMax = 104;// max range for servoX
int laserState = LOW;

long wavelength = 0;// sets delay for x axis (wavelength)
int amplitude = 6;//sets amplitude (up and down) for waves

unsigned long previousMillis = 0;
unsigned long timer = 5000;

void setup()
{  
  Serial.begin(9600);
  servoX.attach(9);
  servoY.attach(10);
  pinMode(laserPin, OUTPUT);
  pinMode(potPin, INPUT);

  //Calibrate X Axis
  int i=0;
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

  digitalWrite(laserPin, HIGH);
  for(float i = servoXMin;i < servoXMax;i++){
    delay(wavelength);
    servoX.write(i);
    servoY.write(sin(i)*amplitude +70);
  }//end of for loop 1

  for(float i = servoXMax; i> servoXMin; i--){
    delay(wavelength);
    servoX.write(i);
    servoY.write(sin(i+10)*amplitude +70);
  }//end of for loop





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




















