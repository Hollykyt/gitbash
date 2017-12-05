#include <TimerOne.h>
#define M1A 2
#define M1B 4
#define M1PWM 9
#define M1EN 6
#define M1CS A0
#define M1EA 3
#define M1EB A4
volatile long int M1Pos = 0;

void INT_m1en(){
  if (digitalRead(M1EA) == digitalRead(M1EB)) {
    M1Pos--;
  } else {
    M1Pos++;
  }
}

#define M2A 7
#define M2B 8
#define M2PWM 10
#define M2EN 12
#define M2CS A1


int32_t m1posg = 5000;
void setup() {
  Serial.begin(250000);
  while(!Serial);
  Serial.setTimeout(600000000);
  Serial.println("yay");
  m1posg = Serial.parseInt();
  Timer1.initialize(40);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M1EN, OUTPUT);
  pinMode(M1CS, INPUT);
  digitalWrite(M1EN, HIGH);
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  //digitalWrite(M1PWM, LOW);
  Timer1.pwm(M1PWM, 512);

  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M2EN, OUTPUT);
  pinMode(M2CS, INPUT);
  digitalWrite(M2EN, HIGH);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  Timer1.pwm(M2PWM, 512);
  
  
  attachInterrupt(digitalPinToInterrupt(M1EA), INT_m1en, CHANGE);
}

int32_t c=0;
int32_t m1pos_err;
int32_t epsilon = 1;
int32_t m1c;
int32_t m1int;
byte f=1;
float m2vel, m2err;
const int32_t kpp = 5;

void loop() {
  m1pos_err = m1posg - M1Pos;
  m1c = m1pos_err * kpp;
  //m1int += 
  if(abs(m1pos_err) > epsilon){
  if(m1c>0){
     digitalWrite(M1A, HIGH);
     digitalWrite(M1B, LOW);
  }else{
     digitalWrite(M1A, LOW);
     digitalWrite(M1B, HIGH);
  }
  m1c = abs(m1c);
  if (m1c>1023){
    c=1023;
  }else if (m1c<50){
    c = 50;
  }else{
    c = m1c;
  }
  Serial.println(M1Pos);
  Timer1.pwm(M1PWM, c);
}else{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, HIGH);
  Timer1.pwm(M1PWM, 255);
  //asm volatile ("  jmp 0");  
}
  delayMicroseconds(3000);
}

