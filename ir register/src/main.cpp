// #include <Arduino.h>
// #include <IRremoteESP8266.h>
// #include <IRrecv.h>
// #include <IRutils.h>

// // An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// // board).
// // Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
// // Note: GPIO 14 won't work on the ESP32-C3 as it causes the board to reboot.
// #ifdef ARDUINO_ESP32C3_DEV
// const uint16_t kRecvPin = 10; // 14 on a ESP32-C3 causes a boot loop.
// #else                         // ARDUINO_ESP32C3_DEV
// const uint16_t kRecvPin = 35;
// #endif                        // ARDUINO_ESP32C3_DEV

// IRrecv irrecv(kRecvPin);

// decode_results results;

// void setup()
// {
//   Serial.begin(115200);
//   irrecv.enableIRIn(); // Start the receiver
//   while (!Serial)      // Wait for the serial connection to be establised.
//     delay(50);
//   Serial.println();
//   Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
//   Serial.println(kRecvPin);
// }

// void loop()
// {
//   if (irrecv.decode(&results))
//   {
//     // print() & println() can't handle printing long longs. (uint64_t)
//     serialPrintUint64(results.value, HEX);
//     Serial.println("");
//     irrecv.resume(); // Receive the next value
//   }
//   delay(100);
// }

#include <Arduino.h>

void setup()
{
  Serial2.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (Serial2.available() > 0)
  {
    char input = Serial2.read();

    Serial.println(input);
  }
  delay(100);
}