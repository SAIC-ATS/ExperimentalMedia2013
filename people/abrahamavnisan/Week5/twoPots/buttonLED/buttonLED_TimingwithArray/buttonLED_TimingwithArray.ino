const int numButts = 3;

int ledPin[numButts] = {9 ,10, 11};
//int buttonPin[numButts] = {2, 3, 4};
//int lastButtonState[numButts] = {LOW, LOW, LOW};
int ledState[numButts] = {LOW, LOW, LOW};
int ledDelay[numButts] = {250, 500, 1000};
long nextBlink[numButts] = {0, 0, 0};

void setup()
{
  //Serial.begin(9600);
  
  for(int i = 0; i<numButts; i++)
  {
    pinMode(ledPin[i], OUTPUT);
    //pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

void loop()
{
  /*
   for(int i = 0; i<numButts; i++)
   {
    int tempButtonValue = !digitalRead(buttonPin[i]);
    
    if(tempButtonValue != lastButtonState[i])
    {
      //we went from high to low or low to high
      if(tempButtonValue == HIGH)
      {
        ledState[i] = !ledState[i];
      }
    }
    
    else
    {
      //the button is either pressed or not but hasn't changed
      //since we checked last time
    }
    
    //Serial.println(tempButtonValue);
    
    digitalWrite(ledPin[i], ledState[i]);
    
    lastButtonState[i] = tempButtonValue;
   } 
   */
   long now = millis();
   
   for(int i = 0; i<numButts; i++)
   {
      if(now > nextBlink[i])
      {
        nextBlink[i] = now + ledDelay[i];
        ledState[i] = !ledState[i]; //toggle state of led
      }
     digitalWrite(ledPin[i], ledState[i]);
   }
}


