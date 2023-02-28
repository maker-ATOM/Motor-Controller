// runs on motor controller

#include <Wire.h>

#define drivePWMpin 6
#define driveDIRpin 8
#define steerPWMpin 10
#define steerDIRpin 14

int PWM = 0;
int driveDIR = 0;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);

  pinMode(drivePWMpin, OUTPUT);
  pinMode(driveDIRpin, OUTPUT);
}

void loop() {
}


void receiveEvent() {
  while (Wire.available() > 0) {
    if (Wire.read() == 6) {
      PWM = Wire.read();
      digitalWrite(driveDIRpin, driveDIR);
      analogWrite(drivePWMpin, PWM);
    }
  }
}