const int num = 3;
const int ledPin[num] =    {4,5,6};        
int ledState[num] ={ LOW,LOW, LOW};
int ledDelays[num] = { 250,500,1000};
long nextBlink[num] = { 0,0,0};

void setup() {
  for(int i =0; i<num ; i++){
    pinMode(ledPin[i], OUTPUT);        }
}

void loop(){
  long now = millis();//millis since your arduino started 45d?
  for(int i =0; i < num; i++){
    digitalWrite(ledPin[i], ledState[i]);
    if (now > nextBlink[i]){
      nextBlink[i]  = now + ledDelays[i];
      ledState[i] = !ledState[i]; 
  }
digitalWrite(ledPin[i], ledState[i]);
}
}
