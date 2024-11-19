#include <Arduino.h>

int echopin = 18;
int trig = 19;
float echo;
int k;
void setup()
{
  Serial.begin(115200);
  
  pinMode(trig, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(1);
  k = pulseIn(echopin, HIGH);
  echo = (k * .0343)/2;
  Serial.println(echo);
  if(echo < 2){
    digitalWrite(2, LOW);
  }
  else{
    digitalWrite(2, HIGH);
  }
  delay(100);
}