#include <Wire.h>

#define led_pin 9

#define ENCA 3
#define ENCB 4
#define PWM 10
#define DIR 14 

#define DPWM 6
#define DDIR 8

int speed = 0;
int deg = 0;

// PID definitions
volatile int posi = 0;
int High_count = 250;
int setpoint=125, direction=0;
float pwm = 0;
float e;
float kp = 3.0;
float diff = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  Wire.begin(3);
  Wire.onReceive(receiveEvent);
  pinMode(PWM, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(DIR, OUTPUT);
  pinMode(DPWM, OUTPUT);
  pinMode(DDIR, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

}

void loop() {
  dispData();
  computePID();
}

void dispData(){
  if (deg > 127){
    digitalWrite(led_pin, HIGH);
  }
  else{
    digitalWrite(led_pin, LOW);
  }
}

void computePID(){
  setpoint = map(deg, 0, 255, 0, High_count);
  e = setpoint - posi;
  pwm = kp * e;
  if (pwm > 0){
    direction = 0;
  }
  else{
    direction = 1;
  }
  pwm = abs(pwm);
  pwm = constrain(pwm, 0, 255);
  speed = constrain(speed, 0, 255);

  if (speed > 127){
    digitalWrite(DDIR, 0);
    analogWrite(DPWM, speed);
  }
  else{
    digitalWrite(DDIR, 1);
    analogWrite(DPWM, speed);
  }
  digitalWrite(DIR, direction);
  analogWrite(PWM, pwm);
}

void receiveEvent(int16_t byteCount) {
  while (Wire.available() > 0) {
    if (Wire.read() == 6) {
    deg = Wire.read();
    speed = Wire.read();
    }
  }
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}