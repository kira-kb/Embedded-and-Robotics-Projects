#include <Arduino.h>
#include <WiFiManager.h> 

void setup() {
  WiFi.mode(WIFI_STA); 
  // the default is STA+AP station + access point
  // we want the esp32 ap mode at start but we want station mode endup with that is why we set it to WiFi.mode(WIFI_STA)

  Serial.begin(115200);

  pinMode(2, OUTPUT);
  
  WiFiManager wm; // creating WiFiManager instance

  wm.resetSettings(); // reset settings wipe stored data this is for testing mode

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("automotion", "123456789"); // password protected ap
  // it returns boolean (TURUE / FALSE) 

  if (!res) Serial.println("sorry, faild to connect");

  if (res) Serial.println("connected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
}