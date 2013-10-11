// The pin that powers the positive end of the LED
int ledPower1 = 2;
int ledPower2 = 3;

// The possible paths for current through the LED circuits and back
// into the arduino
int ledPosition1 = A0;
int ledPosition2 = A3;

// The threshold is set up the voltage through an LED versus straight
// through the circuit
int ledConnectedThreshold = 950;

// The values that the LEDs can take on
const int ON = 255;
const int TEST = 20;
const int OFF = 5;
int led1State = ON;
int led2State = ON;

// Variables that allow the state of the system (two LEDS on/off) to be
// captured in a single byte
const byte SYSTEM_ON_ON = 0;
const byte SYSTEM_ON_OFF = 1;
const byte SYSTEM_OFF_ON = 2;
const byte SYSTEM_OFF_OFF = 3;
byte systemLightState = SYSTEM_ON_ON;

void setup() {                
  pinMode(ledPower1, OUTPUT);        
  pinMode(ledPower2, OUTPUT);    
  pinMode(ledPosition1, INPUT);
  pinMode(ledPosition2, INPUT);
  analogWrite(ledPower1, led1State);
  analogWrite(ledPower2, led2State);
  Serial.begin(9600);
}

void loop() { 
  
  // Read in the current state of the system according to unity
  String buffer = "";
  while (Serial.available() > 0) {
    char in = Serial.read();
    if (in == '\r') {}
    else if (in == '\n') {
      int newState = buffer.toInt();
      if (newState >= 0 && newState <= 3) systemLightState = newState;
      buffer = "";
    }
    else buffer += in;
  }
  
  // Update the LED states according to the message read from unity
  if (systemLightState == SYSTEM_ON_ON) {
     led1State = ON;
     led2State = ON;
  }   
  else if (systemLightState == SYSTEM_ON_OFF) {
     led1State = ON;
     led2State = OFF;
  }     
  else if (systemLightState == SYSTEM_OFF_ON) {
     led1State = OFF;
     led2State = ON;
  }  
  else if (systemLightState == SYSTEM_OFF_OFF) {
     led1State = OFF;
     led2State = OFF;
  }    
  
  // Check whether the LEDs are connected
  //   Turn all LEDS on for a brief flash in order to detect
  //     if they are connected
  //   Read all the voltages coming from the LED circuits
  //   Restore the appropriate state to the LEDs
  //   Compare each voltage against the threshold (smaller voltage means LED is drawing power)
  if (ledPower1 < TEST) analogWrite(ledPower1, TEST);
  if (ledPower2 < TEST) analogWrite(ledPower2, TEST);
  int ledPath1Voltage = analogRead(ledPosition1);
  int ledPath2Voltage = analogRead(ledPosition2);  
  analogWrite(ledPower1, led1State);
  analogWrite(ledPower2, led2State);    
  boolean led1Connected = ledPath1Voltage<=ledConnectedThreshold;
  boolean led2Connected = ledPath2Voltage<=ledConnectedThreshold;
  
  // Send the state of the connections to Unity
  byte outByte = 4;
  if (led1Connected && led2Connected) outByte = 4;
  else if (led1Connected && !led2Connected) outByte = 5;
  else if (!led1Connected && led2Connected) outByte = 6;
  else if (!led1Connected && !led2Connected) outByte = 7;
  Serial.println(outByte);
  
  delay(30);   
}

