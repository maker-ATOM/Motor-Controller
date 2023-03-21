// runs on ESP32

#include <Wire.h>

int pod1pow = 0;
char ack = 6;

void setup() {

  Wire.begin();
}

void loop() {

  pod1pow++;
  pod1();
  delay(20);
}

void pod1() {
  Wire.beginTransmission(4);
  Wire.write(ack);
  Wire.write(pod1pow);
  Wire.endTransmission();
}