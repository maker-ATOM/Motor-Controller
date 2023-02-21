// runs on ESP32

#include <Wire.h>

int led = 0;
int buzz = 1000;
char ack = 6;

void setup() {

  Wire.begin();
}

void loop() {

  Wire.beginTransmission(4);
  Wire.write(ack);
  Wire.write(led);
  Wire.write(buzz);
  Wire.endTransmission();

  led = !led;
  buzz = led * 100 + 100;
  delay(500);
}