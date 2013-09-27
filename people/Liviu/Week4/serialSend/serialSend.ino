
int potPin = A0;
int potPin2 = A1;
int led = 9;



void setup(){
Serial.begin(9600);
pinMode (potPin, INPUT);
pinMode(led, OUTPUT);
}

void loop(){
 
  int VALUE1  = analogRead(potPin);
  int VALUE2  = analogRead(potPin2);
  int brightness = (VALUE1)/4;
  analogWrite(led, brightness);
   
Serial.print(VALUE1); 
Serial.print(","); 
Serial.println(VALUE2);
}
