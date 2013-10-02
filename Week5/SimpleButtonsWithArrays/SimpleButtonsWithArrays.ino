const int numButtons = 3;
int ledPins[numButtons] = { 9, 10, 11 };
int buttonPins[numButtons] = { 2, 3, 4 };

int lastButtonState[numButtons] = { LOW, LOW, LOW };
int ledState[numButtons] = { LOW, LOW, LOW };

void setup() 
{
  // cycle through the input and output pins and set their state
  for(int i = 0; i < numButtons; i++)
  {
    pinMode(ledPins[i],OUTPUT);
    // with input pullup, remember that no external resistor is used.
    // also remember that one leg of the button (or switch, or conductor)
    // goes to the button pin and one leg goes to GROUND.
    // Also remember that when the switch is CLOSED, the pin will read as
    // "LOW".  If you want closed to mean "HIGH" then you need to
    // invert the value by using the ! operator or saying 1 - VALUE;
    pinMode(buttonPins[i],INPUT_PULLUP);
  }
}

void loop() 
{
  for(int i = 0; i < numButtons; i++) {
    
    // read the button value and INVERT the value 
    // using the ! operator.  This turns 1s into 0s
    // and it turns 0s into 1s.
    int tempButtonValue = !digitalRead(buttonPins[i]);  
    
    // detect a change in the sate of our button
    if(tempButtonValue != lastButtonState[i]){
      // there was some change of state in our button
      // either we went from high -> low or
      // went from low -> high
      if(tempButtonValue == HIGH)
      {
        ledState[i] = !ledState[i];
      }
    } else {
      // the button is either pressed or not, but
      // it hasn't changed since last time we checked
    }

    // now make sure that the led is set coorectly
    digitalWrite(ledPins[i],ledState[i]);
    
    // save the last recorded state of the button
    lastButtonState[i] = tempButtonValue;
  }
  
  delay(10);  // just to keep everything under control
}
