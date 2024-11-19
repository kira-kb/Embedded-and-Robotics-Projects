#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
  
  HTTPClient http;

const char* ssid = "ze-amanueal";
const char* password = "Ab1234567";

bool led1on = false;
bool led2on = false;

int led1 = 0;
int led2 = 0;
int ans;

String httpData = "";

void wifiSetup(){
  WiFi.begin(ssid, password);

  Serial.print("\n trying to connect to: ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println("\n connected !!!");
}

void checkLedStatus() {
  
  http.begin("https://autocontrollers.000webhostapp.com/upload.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  delay(100);

  // Serial.println(http.GET());
  if(http.GET() == 200){
    String input = http.getString();

    Serial.println(input);

    StaticJsonDocument<64> doc;
    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    led1 = int(doc["led1"]);
    led2 = int(doc["led2"]);

    digitalWrite(2, led1);
    digitalWrite(5, led2);
  };
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(23, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);

  wifiSetup();
  checkLedStatus();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    if(!digitalRead(23)){
      Serial.println("button 1 pressed");
      if(!led1) {
        Serial.println("....");
        led1 = 1;
        httpData = "led1=" + String(led1) + "&led2=" + String(led2);

        if (ans = http.POST(httpData) > 0){
          Serial.print("http code1: ");
          Serial.println(ans);

          digitalWrite(2, HIGH);
          led1on = !led1on;
          
        }

        }else if(led1){
          Serial.println("***");
          led1 = 0;
          httpData = "led1=" + String(led1) + "&led2=" + String(led2);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(2, LOW);
            led1on = !led1on;
          }
      }else {
        Serial.print("error code1: ");
        Serial.println(ans);
        }
      }

    if(!digitalRead(22)){
      Serial.println("button 2 pressed");
      if(!led2) {
        Serial.println("....");
        led2 = 1;
        httpData = "led1=" + String(led1) + "&led2=" + String(led2);

        if (ans = http.POST(httpData) > 0){
          Serial.print("http code2: ");
          Serial.println(ans);

          digitalWrite(5, HIGH);
          led2on = !led2on;

          String response_body = http.getString();
          Serial.print("Server reply2: ");
          Serial.println(response_body);
        }

        }else if(led2){
          Serial.println("***");
          led2 = 0;
          httpData = "led1=" + String(led1) + "&led2=" + String(led2);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(5, LOW);
            led2on = !led2on;
          }
      }else {
        Serial.print("error code2: ");
        Serial.println(ans);
        }
      }
      checkLedStatus();
    }else wifiSetup();
    delay(200);
}