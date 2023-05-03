#include<Wire.h>
char ack = 6;
int deg = 0;
int controller = 0;
int speed;

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
 readVal();
 sendVal();
 printVal();
}

void readVal(){
  if (Serial.available() > 0){
    char temp;
    temp = Serial.read();
    if (temp == 'c'){
      controller = Serial.parseInt();
    }
    if (temp == 'd'){
      deg = Serial.parseInt();
      deg = map(deg, -180, 180, 0, 255);
    }
    if (temp == 's'){
      speed = Serial.parseInt();
    }
  }
}

void sendVal(){
  speed = constrain(speed, 0, 255);
  deg = constrain(deg, 0, 255);
  Wire.beginTransmission(controller);
  Wire.write(ack);
  Wire.write(deg);
  Wire.write(speed);
  Wire.endTransmission();
}

void printVal(){
  Serial.print("controller");
  Serial.print("\t");
  Serial.print(controller);
  Serial.print("\t");
  Serial.print("degree");
  Serial.print("\t");
  Serial.print(deg);
  Serial.print("\t");
  Serial.print("speed");
  Serial.print("\t");
  Serial.println(speed);

}