int doorbellPin = 33;

void setup() {
  pinMode(doorbellPin, OUTPUT);
}

void loop() {
  digitalWrite(doorbellPin, HIGH);
  delay(100);
  digitalWrite(doorbellPin, LOW);
  delay(100);
}