// runs on motor controller

#include <Wire.h>

#define ledPin 9
#define buzzPin 5

int led = 0;
int buzz = 0;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);

  pinMode(ledPin, OUTPUT);
}

void loop() {
}


void receiveEvent(int16_t byteCount) {
  while (Wire.available() > 0) {
    if (Wire.read() == 6) {
      led = Wire.read();
      buzz = Wire.read();
      digitalWrite(ledPin, led);
      tone(buzzPin, buzz * 10);
    }
  }
}