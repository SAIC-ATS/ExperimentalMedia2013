const int num_leds = 3;
int leds[num_leds] = {11, 10, 9};
int buttons[num_leds] = {4, 5, 6};
boolean buttonState[num_leds] = {0, 0, 0};
boolean ledState[num_leds] = {0, 0, 0};

int ledDelays[num_leds] = {100, 50, 200};
int ledTime[num_leds] = {0, 0, 0};

int elapsedTime = 0;


const int BAUD_RATE = 9600;

void setup()
{
  Serial.begin(BAUD_RATE);
  
  for (int i=0; i<num_leds; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }

}

void loop()
{  
  for (int i=0; i<num_leds; i++) {
    boolean state = digitalRead(buttons[i]);
    
    if (!buttonState[i] && state) ledState[i] = !ledState[i];
    buttonState[i] = state;
    
    analogWrite(leds[i], 255*ledState[i]);
  }
  
  ledState[2] = !ledState[2];
  analogWrite(leds[2], 255*ledState[2]);  
}

