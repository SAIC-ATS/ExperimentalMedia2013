//const int buttonPin0 = 2;
//const int buttonPin1 = 3;
//const int buttonPin2 = 4;
//const int led0 = 9;
//const int led1 = 10;
//const int led2 = 11;

const int numButtons = 3;

int ledPins[numButtons] = {9, 10, 11};
int buttonPins[numButtons] = {2, 3, 4 }; 

int lastButtonState[numButtons] = {LOW, LOW, LOW};
int ledState[numButtons] = {LOW, LOW, LOW};

void setup()
{

  for (int i = 0; i < numButtons; i++)
  {
   pinMode(ledPins[i],OUTPUT);
   pinMode(buttonPins[i], INPUT_PULLUP);   
  }
  
}

void loop() 
{

  for (int i = 0; i < numButtons; i++) {
    
    int tempButtonValue = !digitalRead(buttonPins[i]);
    
    if (tempButtonValue != lastButtonState[i]) {
      //there was a change of state in our button
      //either we went to high -> low or the reverse
      if(tempButtonValue == HIGH) {
        
        ledState[i] = !ledState[i];
    } else {
      //button state has not changed since last time we checked
      
    }
    
    //now make sure that the LED is set correctly
    digitalWrite(ledPins[i],ledState[i]);
    
    lastButtonState[i] = tempButtonValue;
  }
   
   //delay(1);
   
  
}
}
