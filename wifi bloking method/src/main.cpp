#include <Arduino.h>
#include <wifiMulti.h>

#define WIFI_SSID "ze-amanueal"
#define WIFI_PASSWORD "Ab1234567"

WiFiMulti conn;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(2, OUTPUT);

  // we can have multiple wifi or access point we can list available wifis and the code will try to connect to the listed netwotks if the 1st fails it trys the 2nd one it keep trys until it connect 
  // conn.addAccessPoint() = conn.addAP()
  // conn.addAP(WIFI_SSID, WIFI_PASSWORD);
  // conn.addAP(WIFI_SSID, WIFI_PASSWORD);
  conn.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("connecting");
  while(conn.run() != WL_CONNECTED){
    Serial.print('.');
    delay(100);
  }

  Serial.println('\n');
  Serial.print("connected to ");
  Serial.println(WIFI_SSID);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, WiFi.status() == WL_CONNECTED);
}