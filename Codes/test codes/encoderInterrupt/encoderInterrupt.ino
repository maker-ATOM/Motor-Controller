#define ENCA 3
#define ENCB 4
#define led 9

volatile int posi = 0;

void setup() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(led, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
// led blinks if posi is even 
  // int ans = abs(posi % 2);
  // digitalWrite(led, ans);
  
  
  if (posi > 0){
    analogWrite(led, posi);  
  }
  else{
    digitalWrite(led, LOW);   
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