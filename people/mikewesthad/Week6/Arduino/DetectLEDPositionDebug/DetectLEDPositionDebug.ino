byte ledPosition = 0;
byte maxLedPosition = 3;
long int switchDelay = 1000;
long int switchTime = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  long int currentTime = millis();
  if (currentTime>switchTime) {
    ledPosition++;
    if (ledPosition>maxLedPosition) ledPosition = 0;
    switchTime = currentTime + switchDelay;
  }
  Serial.println(ledPosition);
  delay(10);
  
}
