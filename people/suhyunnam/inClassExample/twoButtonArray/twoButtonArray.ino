const int numButtons = 3;
const int numLeds= 3;

const int buttonPin[numButtons] =  {10,11,12};
const int ledPin[numButtons] =    {4,5,6};        

void setup() {
  for(int i =0; i<numButtons ; i++){
    pinMode(ledPin[i], OUTPUT);      
    pinMode(buttonPin[i], INPUT_PULLUP); 
  }
}

void loop(){
  for(int i =0; i < numButtons; i++){
  buttonState[i] = !digitalRead(buttonPin[i]);
  digitalWrite(ledPin[i], !digitalRead(buttonPin[i])); 
}
}
