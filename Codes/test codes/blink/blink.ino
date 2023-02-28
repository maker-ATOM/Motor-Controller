#define ledPin 9
#define buzzPin 5
void setup() {
  pinMode(9, OUTPUT);
  tone(buzzPin, 1000);
}

void loop() {
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(1000);
}