const int pot1Pin = A0;
const int pot2Pin = A1;

void setup() {                
  Serial.begin(9600);
}

void loop() {
  int pot1Value = analogRead(pot1Pin);
  int pot2Value = analogRead(pot2Pin);
  Serial.print(pot1Value); Serial.print(","); Serial.println(pot2Value);
  delay(100);
}
