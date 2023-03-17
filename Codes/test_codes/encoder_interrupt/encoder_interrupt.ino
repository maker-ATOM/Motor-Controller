#define ENCA 3
#define ENCB 4
#define led 9

volatile int posi = 0;

void setup() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(led, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  int ans = abs(posi % 2);
  digitalWrite(led, ans);

}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi--;
  } else {
    posi++;
  }
}