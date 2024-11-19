#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "ze-amanueal";
const char* password = "Ab1234567";

#define BOTToken "5888426281:AAGII-tc96EzVGRvjcbxjzc9R7TM_S77IbA"
#define CHAT_ID "434736451"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTToken, client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(23, INPUT_PULLUP);
  WiFi.mode(WIFI_STA);

  Serial.print("trying to connect to wifi : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(500);
  }

  Serial.println("\n wifi connected!!!");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  bool starterMsg = bot.sendMessage(CHAT_ID, "Bot started up", "");

  if(starterMsg) Serial.println("message delivered");
  else Serial.println("message not delivered");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(23)) {
    Serial.println("button pressed");
    bot.sendMessage(CHAT_ID, "button pressed", "");
  }
}