#define ENCA 3
#define ENCB 4
#define PWM 10
#define DIR 14 
#define led 9

volatile int posi = 0;

int High_count = 550;

int setpoint, direction;
float pwm = 0;
float e;
float kp = 2;
float deg = 30;
float diff = 0;

float dpwm = 0;
int ddir = 0;

void setup() {
  pinMode(PWM, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(DIR, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  setpoint = map(deg, -180, 180, -High_count / 2, High_count / 2);
  e = setpoint - posi;
  if (e>0){
    analogWrite(led, e);
  }
  else{
    digitalWrite(led, LOW);
  }
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

int deadBand(int a) {
  if (a < 10 && a > -10) {
    a = 0;
  }
  return a;
}