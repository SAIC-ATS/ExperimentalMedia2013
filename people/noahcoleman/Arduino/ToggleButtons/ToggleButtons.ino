const int numButtons = 3;

int ledPins[numButtons] = {
  9,10,11};
int buttonPins[numButtons] = {
  2,3,4};

int lastButtonState[numButtons] = {
  LOW, LOW, LOW};
int ledState[numButtons] = {
  LOW, LOW, LOW};  

void setup(){

  for(int i = 0; i < numButtons; i++){
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop(){
  for(int i = 0; i < numButtons; i++)
  {
    int tempButtonValue = !digitalRead(buttonPins[i]);

    if(tempButtonValue != lastButtonState[i]){


      if(tempButtonValue == HIGH){
        ledState[i] = !ledState[i];
      }
    }
    digitalWrite(ledPins[i], ledState[i]); 
    lastButtonState[i] = tempButtonValue; 
  }


}






