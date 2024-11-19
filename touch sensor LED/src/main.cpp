#include <Arduino.h>

// T0 : GPIO 4
// T1 : GPIO 0
// T2 : GPIO 2
// T3 : GPIO 15
// T4 : GPIO 13
// T5 : GPIO 12
// T6 : GPIO 14
// T7 : GPIO 27
// T8 : GPIO 33
// T9 : GPIO 32
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}

void loop() {
  int val = touchRead(4);

  Serial.println(val);

  if (val < 50) digitalWrite(2, HIGH);
  else digitalWrite(2, LOW);
  delay(500);
}
