int dits =500;
int off =500;
int dahs =1000;

void setup(){
  pinMode(13,OUTPUT);
}

void loop(){
//what
signalOn(dits);
signalOn(dahs);
signalOn(dahs);

signalOn(dits);
signalOn(dits);
signalOn(dits);
signalOn(dits);

signalOn(dits);
signalOn(dahs);

signalOn(dahs);

delay(off*2);

//hath
signalOn(dits);
signalOn(dits);
signalOn(dits);
signalOn(dits);

signalOn(dits);
signalOn(dahs);

signalOn(dahs);

signalOn(dits);
signalOn(dits);
signalOn(dits);
signalOn(dits);

delay(off*2);

//god
signalOn(dahs);
signalOn(dahs);
signalOn(dits);

signalOn(dahs);
signalOn(dahs);
signalOn(dahs);

signalOn(dahs);
signalOn(dits);
signalOn(dits);

delay(off*2);

//wrought
signalOn(dits);
signalOn(dahs);
signalOn(dahs);

signalOn(dits);
signalOn(dahs);
signalOn(dits);

signalOn(dahs);
signalOn(dahs);
signalOn(dahs);

signalOn(dits);
signalOn(dits);
signalOn(dahs);

signalOn(dahs);
signalOn(dahs);
signalOn(dits);

signalOn(dits);
signalOn(dits);
signalOn(dits);
delay(off*2);
signalOn(dahs);
delay(off*10);
}

void signalOn(int t_1){
  digitalWrite(13,HIGH);
delay(t_1);
digitalWrite(13,LOW);
delay(off);
}

