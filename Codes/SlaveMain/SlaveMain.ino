#include <Wire.h>

#define ENCA 3
#define ENCB 4
#define PWM 10
#define DIR 14 
#define ledPin 9

int led = 0;
int deg = 0;

// PID definitions
volatile int posi = 0;
int High_count = 550;
int setpoint, direction;
float pwm = 0;
float e;
float kp = 2;
float diff = 0;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(DIR, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  computePID();
  dispData();
}

void dispData(){
        if (deg > 0){
        analogWrite(ledPin, deg);
      }
      else{
        digitalWrite(ledPin, LOW);
      }
}

void computePID(){
  setpoint = map(deg, -180, 180, -High_count / 2, High_count / 2);
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

  digitalWrite(DIR, direction);
  analogWrite(PWM, pwm);
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}

void receiveEvent(int16_t byteCount) {
  while (Wire.available() > 0) {
    if (Wire.read() == 6) {
      deg = Wire.read();
      if (deg & 0x80) { 
        deg = -((~deg + 1) & 0xFF); 
      }
      
    }
  }
}