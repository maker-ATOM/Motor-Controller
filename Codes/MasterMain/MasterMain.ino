#include <PS4Controller.h>
#include <Wire.h>

char ack = 6;
int speed = 0;
int16_t deg;

float x, y;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  PS4.begin("d0:49:7c:9f:da:a2");
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
  deg = map(deg, -180, 180, 0, 255);
  int8_t data_high = (int8_t)(deg >> 8);
  int8_t data_low = (int8_t)deg;
  Wire.beginTransmission(4);
  Wire.write(ack);
  Wire.write(data_high);
  Wire.write(data_low); 
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