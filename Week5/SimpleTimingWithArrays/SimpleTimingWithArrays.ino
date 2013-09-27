static const int numLEDs = 3;
int ledPins[numLEDs] = { 9, 10, 11 }; // the pins for each LED
int ledState[numLEDs] = { LOW, LOW, LOW }; // the state of each LED
long ledDelays[numLEDs] = { 250, 500, 1000 }; // the delay for each LED
long nextBlinkTime[numLEDs] = { 0, 0, 0 }; // our scheduled next blink time

void setup() 
{
  // cycle through the LED pins and set each to output
  for(int i = 0; i < numLEDs; i++) 
  {
    pinMode(ledPins[i],OUTPUT);
  }
}

void loop() 
{
  long now = millis(); // get the current time
  for(int i = 0; i < numLEDs; i++) // cycle through the leds
  {
    if(now > nextBlinkTime[i]) // if the current time (now) is greater than the scheduled next blink time ...
    {
      nextBlinkTime[i] = now + ledDelays[i]; // schedule the next blink
      ledState[i] = !ledState[i]; // toggle the state of my led
    }
    digitalWrite(ledPins[i],ledState[i]); // tell the LED what to do
  }
}
