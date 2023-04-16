#include <Wire.h>

#define ENCA 3
#define ENCB 4
#define PWM 10
#define DIR 14 
#define ledPin 9

int led = 0;
int16_t deg = 0;

// PID definitions
volatile int posi = 0;
int High_count = 250;
int setpoint=125, direction=0;
float pwm = 0;
float e;
float kp = 3.0;
float diff = 0;

void setup() {
  Wire.begin(11);
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(DIR, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  
  delay(2000);
}

void loop() {
  computePID();
  dispData();
}

void dispData(){
        if (deg > 127){
        digitalWrite(ledPin, HIGH);
      }
      else{
        digitalWrite(ledPin, LOW);
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
    uint8_t data_high = Wire.read(); 
    uint8_t data_low = Wire.read(); 
    
    deg = (int16_t)((data_high << 8) | data_low); // combine the high and low bytes into a signed integer
  }
  }
}