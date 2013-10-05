
const int numLEDs = 3;
int ledPins[numLEDs] = {9,10,11};
int buttonPins[numLEDs] = {2,3,4};
int lastButtonState[numLEDs] = {LOW, LOW, LOW};
int buttonState[numLEDs] = {LOW, LOW, LOW};
int ledState[numLEDs] = {LOW, LOW, LOW };
char vButtonState[numLEDs] = {'0','0','0'}; //states for virtual buttons
byte vLedState[numLEDs] = {'0','0','0'}; //states for virtual leds on the screeN) 

void setup() 
{
  Serial.begin(9600);
  vLedState[0] = '0';
  vLedState[1] = '0';
  vLedState[2] = '0';
  
  for(int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  } 
}

void loop(){
  //long now = millis();  
  
  if (Serial.available()>0) {
    // read the incoming byte
    Serial.readBytes(vButtonState, 3);
    Serial.write(vLedState, 3);
  }
     
  for(int i = 0; i < numLEDs; i++){
    
    if (vButtonState[i] == '1') {
      ledState[i] = HIGH;
    } else {
      ledState[i] = LOW;
    }
    
    digitalWrite(ledPins[i], ledState[i]);
      
    int tempButtonValue = digitalRead(buttonPins[i]);
    if (tempButtonValue == HIGH) {
      vLedState[i] = '1'; 
    } else {
      vLedState[i] = '0' ;
    }
    
    /*if(tempButtonValue != lastButtonState[i]){ // button is pushed !!
      if(tempButtonValue == HIGH) { // button is pushed to HIGH!
        vLedState[i] = !vLedState[i];
      } else {
      }
      lastButtonState[i] = tempButtonValue;
    }*/

  }
      
  //Serial.print(vLedState);
 
}
  

