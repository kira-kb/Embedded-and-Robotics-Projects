#include <Arduino.h>

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char val;

void setup() {
  Serial.begin(115200);

  SerialBT.begin("kira_esp");
  Serial.println("\n Bluetooth Started! Ready to pair...");

  pinMode(2, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
}

void loop() {

  while (SerialBT.available() > 0) {
    val = 0;
    
    val = SerialBT.read();

    Serial.println(val);

    if (val == 'A' )digitalWrite(2, HIGH);
    if( val == 'a') digitalWrite(2, LOW); 

    if (val == 'B' )digitalWrite(18, HIGH);
    if( val == 'b') digitalWrite(18, LOW); 

    if (val == 'C' )digitalWrite(19, HIGH);
    if( val == 'c') digitalWrite(19, LOW); 

    if (val == 'D' )digitalWrite(21, HIGH);
    if( val == 'd') digitalWrite(21, LOW); 

    if (val == 'E' )digitalWrite(22, HIGH);
    if( val == 'e') digitalWrite(22, LOW); 

    if (val == 'F' )digitalWrite(23, HIGH);
    if( val == 'f') digitalWrite(23, LOW); 

    if (val == 'Z' ){
      digitalWrite(2, HIGH);
      digitalWrite(18, HIGH);
      digitalWrite(19, HIGH);
      digitalWrite(21, HIGH);
      digitalWrite(22, HIGH);
      digitalWrite(23, HIGH);
      }
    if( val == 'z') {
      digitalWrite(2, LOW);
      digitalWrite(18, LOW);
      digitalWrite(19, LOW);
      digitalWrite(21, LOW);
      digitalWrite(22, LOW);
      digitalWrite(23, LOW);
      }
  }

}