// runs on motor controller

#include <Wire.h>

#define ledPin 9

int led = 0;

void setup() {
  Wire.begin(6);
  Wire.onReceive(receiveEvent);

  pinMode(ledPin, OUTPUT);
}

void loop() {
  dispData();
}

void dispData(){
  int ans = abs(led % 2);
  digitalWrite(ledPin, ans);
}

void receiveEvent(int16_t byteCount) {
  while (Wire.available() > 0) {
    if (Wire.read() == 6) {
      led = Wire.read();
    }
  }
}