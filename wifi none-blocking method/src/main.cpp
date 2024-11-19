#include <Arduino.h>
#include <WiFi.h>

#define WIFI_SSID "ze-amanueal"
#define WIFI_PASSWORD "Ab1234567"
// defining wifi instances

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // passing to the begin method to start connection

  Serial.println("starting");
}

bool isConnected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !isConnected){
    Serial.println("connnected");
    digitalWrite(2, HIGH);
  }

  if (WiFi.status() != WL_CONNECTED){
    digitalWrite(2, !digitalRead(2));
    delay(500);
  }
}