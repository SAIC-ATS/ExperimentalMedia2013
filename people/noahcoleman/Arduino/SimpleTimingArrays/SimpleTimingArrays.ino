const int numLeds = 3;

int ledPins[numLeds] = {
  9,10,11};
int ledState[numLeds] = {
  LOW, LOW, LOW};
long ledDelays[numLeds] = {
  250, 500, 1000};
long nextBlink[numLeds] = {
  0,0,0};



void setup(){

  for(int i = 0; i < numLeds; i++){
    pinMode(ledPins[i], OUTPUT);

  }
}

void loop(){
long now = millis(); //get current time


  for(int i = 0; i < numLeds; i++){
if(now > nextBlink[i]) {
  nextBlink[i] = now + ledDelays[i];//schedule next blink
  ledState[i] = !ledState[i]; //toggle led state
  


    digitalWrite(ledPins[i], ledState[i]);

  }
}
}






