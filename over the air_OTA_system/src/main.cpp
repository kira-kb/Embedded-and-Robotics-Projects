#include <Arduino.h>

// to update the firmware send .bin file in platformio .pio/build/nodemcu32s/firmware.bin

#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

const char* ssid = "ze-amanueal";
const char* password = "Ab1234567";

AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
pinMode(23, INPUT_PULLUP);

Serial.begin(115200);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);
Serial.println("WiFi Connection Attempt");

while(WiFi.status() != WL_CONNECTED)
{
  delay(400);
  Serial.print(".");  
}

Serial.println("\n Connected to : ");
Serial.print(ssid);
Serial.print("IP Address for ESP32: ");
Serial.println(WiFi.localIP());

server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
  request->send(200,"text/plain","this is from kira general home automotion OTA v2.0 - Update wirelessly");});

  AsyncElegantOTA.begin(&server);
  // server.begin();

  Serial.println("Elegant OTA Initiated");
  Serial.println("HTTP Server Has started Sucessfully");
  Serial.print(WiFi.localIP());
  Serial.println("/update");
}

bool isOn = false;

void loop() {
  // put your main code here, to run repeatedly:
   int val = touchRead(4);

  // Serial.println(val);
  if (val < 50 && !isOn) {
    digitalWrite(2, HIGH);
    server.begin();
    isOn = true;
    }
  // else {
  //   digitalWrite(2, LOW);
  //   };

  if (!digitalRead(23) && isOn){
    digitalWrite(2, LOW);
    server.end();
    isOn = false;
  }
  delay(500);
}