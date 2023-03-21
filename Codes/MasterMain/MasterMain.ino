#include <PS4Controller.h>
#include <Wire.h>

char ack = 6;
int speed = 0;
int deg;

float x, y;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  PS4.begin("f8:9e:94:74:ed:90");
}

void loop() {
  if (PS4.isConnected()) {
  readValue();
  pod1();
  printData();
  }
  // while(!Serial.available()){
  //   delay(10);
  // }
  // deg = Serial.parseInt();
  // pod1();
  delay(20);
}

void readValue(){
  x = PS4.LStickX();
  y = PS4.LStickY();

  x = deadBand(x);
  y = deadBand(y);

  float rad = atan2(y, x);
  deg = rad * (180 / 3.14);
}

void pod1() {
  Wire.beginTransmission(4);
  Wire.write(ack);
  Wire.write(deg & 0xFF); 
  Wire.write((deg >> 8) & 0xFF);
  Wire.endTransmission();
}

void printData(){
  Serial.print("deg");
  Serial.print("\t");
  Serial.println(deg);
}

int deadBand(int a) {
  if (a < 10 && a > -10) {
    a = 0;
  }
  return a;
}