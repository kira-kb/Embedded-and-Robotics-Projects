#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// #include <LittleFS.h>
  
  HTTPClient http;

const char* ssid = "ze-amanueal";
const char* password = "Ab1234567";

char Incoming_value = 0;

int wifi_counter = 0;

int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int led5 = 0;
int led6 = 0;

int ans;

String httpData = "";

void wifiSetup(){
  WiFi.begin(ssid, password);

  Serial.print("\n trying to connect to: ");
  Serial.println(ssid);

  int counter = 0;

  while(WiFi.status() != WL_CONNECTED && counter < 5){
    Serial.print(". ");
    counter++;
    Serial.print(counter);
    if(counter >= 5) {
      Serial.println("cannot connect to the wifi");
      break;
    }
    delay(300);
  }
  if (WiFi.status() == WL_CONNECTED) Serial.println("\n connected !!!");
}

void checkLedStatus() {
  
  http.begin("https://autocontrollers.000webhostapp.com/upload.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  delay(100);

  // Serial.println(http.GET());
  if(http.GET() == 200){
    String input = http.getString();

    Serial.println(input);

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    led1 = int(doc["led1"]);
    led2 = int(doc["led2"]);
    led3 = int(doc["led3"]);
    led4 = int(doc["led4"]);
    led5 = int(doc["led5"]);
    led6 = int(doc["led6"]);

    digitalWrite(4, led1);
    digitalWrite(22, led2);
    digitalWrite(23, led3);
    digitalWrite(21, led4);
    digitalWrite(18, led5);
    digitalWrite(19, led6);
  };
}


void offlineController(int lamp, int button){
  // Serial.print("button: ");
  // Serial.println(button);
  if (button == 1 || Incoming_value == 'A' || Incoming_value == 'a'){
    if(!led1 || Incoming_value == 'A') {
        // Serial.println(lamp);
        led1 = 1;
        digitalWrite(lamp, HIGH);
        }else if(led1 || Incoming_value == 'a'){
          // Serial.println("***" + String(led1));
          led1 = 0;
          digitalWrite(lamp, LOW);
      }
  }
    if (button == 2 || Incoming_value == 'B' || Incoming_value == 'b'){
    if(!led2 || Incoming_value == 'B') {
        // Serial.println(lamp);
        led2 = 1;
        digitalWrite(lamp, HIGH);
        }else if(led2 || Incoming_value == 'b'){
          // Serial.println("***" + String(led2));
          led2 = 0;
          digitalWrite(lamp, LOW);
      }
  }
    if (button == 3 || Incoming_value == 'C' || Incoming_value == 'c'){
    if(!led3 || Incoming_value == 'C') {
        // Serial.println(lamp);
        led3 = 1;
        digitalWrite(lamp, HIGH);
        }else if(led3 || Incoming_value == 'c'){
          // Serial.println("***" + String(led3));
          led3 = 0;
          digitalWrite(lamp, LOW);
      }
  }
    if (button == 4 || Incoming_value == 'D' || Incoming_value == 'd'){
    if(!led4 || Incoming_value == 'D') {
        // Serial.println(lamp);
        led4 = 1;
        digitalWrite(lamp, HIGH);
        }else if(led4 || Incoming_value == 'd'){
          // Serial.println("***" + String(led4));
          led4 = 0;
          digitalWrite(lamp, LOW);
      }
  }
  
  if (button == 5 || Incoming_value == 'E' || Incoming_value == 'e'){
    if(!led5 || Incoming_value == 'E') {
        // Serial.println(lamp);
        led5 = 1;
        digitalWrite(lamp, HIGH);
        }else if(led5 || Incoming_value == 'e'){
          // Serial.println("***" + String(led5));
          led5 = 0;
          digitalWrite(lamp, LOW);
      }
  }
    if (button == 6 || Incoming_value == 'F' || Incoming_value == 'f'){
    if(!led6 || Incoming_value == 'F') {
        // Serial.println(lamp);
        led6 = 1;
        digitalWrite(lamp, HIGH);
        }else if(led6 || Incoming_value == 'f'){
          // Serial.println("***" + String(led6));
          led6 = 0;
          digitalWrite(lamp, LOW);
      }
  }
    
  wifiSetup();
}


void sendStatus(int lamp, int button) {
  Serial.print("button: ");
  // http.
  Serial.println(button);
  if(button == 1 || Incoming_value == 'A' || Incoming_value == 'a'){
      if(!led1 || Incoming_value == 'A') {
        Serial.println(lamp);
        led1 = 1;

          httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

        if (ans = http.POST(httpData) > 0){
          // Serial.print("http code");
          // Serial.print(String(led1) + ": ");
          Serial.println(ans);

          digitalWrite(lamp, HIGH);          
        }

        }else if(led1 || Incoming_value == 'a'){
          Serial.println("***" + String(led1));
          led1 = 0;
          
            httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

          if (ans = http.POST(httpData) > 0){
            digitalWrite(lamp, LOW);
          }
      }else {
          // Serial.print("error code");
          // Serial.print(String(lamp) + ": ");
          // Serial.println(ans);
          offlineController(lamp, button);
        }
  }
  if(button == 2 || Incoming_value == 'B' || Incoming_value == 'b'){
      if(!led2 || Incoming_value == 'B') {
        // Serial.println(lamp);
        led2 = 1;

          httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

        if (ans = http.POST(httpData) > 0){
          // Serial.print("http code");
          // Serial.print(String(led2) + ": ");
          // Serial.println(ans);

          digitalWrite(lamp, HIGH);          
        }

        }else if(led2 || Incoming_value == 'b'){
          // Serial.println("***" + String(led2));
          led2 = 0;

            httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(lamp, LOW);
          }
      }else {
          // Serial.print("error code");
          // Serial.print(String(lamp) + ": ");
          // Serial.println(ans);
          offlineController(lamp, button);
        }
  }
  if(button == 3 || Incoming_value == 'C' || Incoming_value == 'c'){
      if(!led3 || Incoming_value == 'C') {
        // Serial.println(lamp);
        led3 = 1;

          httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

        if (ans = http.POST(httpData) > 0){
          // Serial.print("http code");
          // Serial.print(String(led3) + ": ");
          // Serial.println(ans);

          digitalWrite(lamp, HIGH);          
        }

        }else if(led3 || Incoming_value == 'c'){
          // Serial.println("***" + String(led3));
          led3 = 0;

            httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(lamp, LOW);
          }
      }else {
          // Serial.print("error code");
          // Serial.print(String(lamp) + ": ");
          // Serial.println(ans);
          offlineController(lamp, button);
        }
  }
  if(button == 4 || Incoming_value == 'D' || Incoming_value == 'd'){
      if(!led4 || Incoming_value == 'D') {
        // Serial.println(lamp);
        led4 = 1;

          httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

        if (ans = http.POST(httpData) > 0){
          // Serial.print("http code");
          // Serial.print(String(led4) + ": ");
          // Serial.println(ans);

          digitalWrite(lamp, HIGH);          
        }

        }else if(led4 || Incoming_value == 'd'){
          // Serial.println("***" + String(led4));
          led4 = 0;

            httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(lamp, LOW);
          }
      }else {
          // Serial.print("error code");
          // Serial.print(String(lamp) + ": ");
          // Serial.println(ans);
          offlineController(lamp, button);
        }
  }
  if(button == 5 || Incoming_value == 'E' || Incoming_value == 'e'){
      if(!led5 || Incoming_value == 'E') {
        // Serial.println(lamp);
        led5 = 1;

          httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

        if (ans = http.POST(httpData) > 0){
          // Serial.print("http code");
          // Serial.print(String(led5) + ": ");
          // Serial.println(ans);

          digitalWrite(lamp, HIGH);          
        }

        }else if(led5 || Incoming_value == 'e'){
          // Serial.println("***" + String(led5));
          led5 = 0;

            httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(lamp, LOW);
          }
      }else {
          // Serial.print("error code");
          // Serial.print(String(lamp) + ": ");
          // Serial.println(ans);
          offlineController(lamp, button);
        }
  }
  if(button == 6 || Incoming_value == 'F' || Incoming_value == 'f'){
      if(!led6 || Incoming_value == 'F') {
        // Serial.println(lamp);
        led6 = 1;

          httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

        if (ans = http.POST(httpData) > 0){
          // Serial.print("http code");
          // Serial.print(String(led6) + ": ");
          // Serial.println(ans);

          digitalWrite(lamp, HIGH);          
        }

        }else if(led6 || Incoming_value == 'f'){
          // Serial.println("***" + String(led6));
          led6 = 0;

            httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);
          
          if (ans = http.POST(httpData) > 0){
            digitalWrite(lamp, LOW);
          }
      }else {
          // Serial.print("error code");
          // Serial.print(String(lamp) + ": ");
          // Serial.println(ans);
          offlineController(lamp, button);
        }
  }

}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);

  pinMode(13, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);

  wifiSetup();
  checkLedStatus();
}

void loop() {
/////////////////////////////////////////////
  if (wifi_counter >= 100) {
    wifiSetup();
    wifi_counter = 0;
    }
///////////////////////////////////////

  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.println(Incoming_value);
  }

    if (WiFi.status() == WL_CONNECTED && Incoming_value){

      if(Incoming_value == 'A') sendStatus(4, 1); 
      if(Incoming_value == 'a') sendStatus(4, 1);   

      if(Incoming_value == 'B') sendStatus(22, 2);
      if(Incoming_value == 'b') sendStatus(22, 2); 

      if(Incoming_value == 'C')  sendStatus(23, 3); 
      if(Incoming_value == 'c')  sendStatus(23, 3);

      if(Incoming_value == 'D')  sendStatus(21, 4); 
      if(Incoming_value == 'd')  sendStatus(21, 4); 
                            
      if(Incoming_value == 'E') sendStatus(18, 5); 
      if(Incoming_value == 'e') sendStatus(18, 5); 

      if(Incoming_value == 'F')  sendStatus(19, 6); 
      if(Incoming_value == 'f')  sendStatus(19, 6);
    }
      else if (WiFi.status() != WL_CONNECTED && Incoming_value){
        if(Incoming_value == 'A') offlineController(4, 1); 
        if(Incoming_value == 'a') offlineController(4, 1);   

        if(Incoming_value == 'B') offlineController(22, 2);
        if(Incoming_value == 'b') offlineController(22, 2); 

        if(Incoming_value == 'C')  offlineController(23, 3); 
        if(Incoming_value == 'c')  offlineController(23, 3);

        if(Incoming_value == 'D')  offlineController(21, 4); 
        if(Incoming_value == 'd')  offlineController(21, 4); 
                              
        if(Incoming_value == 'E') offlineController(18, 5); 
        if(Incoming_value == 'e') offlineController(18, 5); 

        if(Incoming_value == 'F')  offlineController(19, 6); 
        if(Incoming_value == 'f')  offlineController(19, 6);

  }    

  if (WiFi.status() == WL_CONNECTED){
    if(!digitalRead(13)) sendStatus(4, 1);
    if(!digitalRead(25)) sendStatus(22, 2);
    if(!digitalRead(26)) sendStatus(23, 3);
    if(!digitalRead(27)) sendStatus(21, 4);
    if(!digitalRead(32)) sendStatus(18, 5);
    if(!digitalRead(33)) sendStatus(19, 6);
    
    checkLedStatus();
    }else {
      if(!digitalRead(13)) offlineController(4, 1);
      if(!digitalRead(25)) offlineController(22, 2);
      if(!digitalRead(26)) offlineController(23, 3);
      if(!digitalRead(27)) offlineController(21, 4);
      if(!digitalRead(32)) offlineController(18, 5);
      if(!digitalRead(33)) offlineController(19, 6);
      // wifiSetup();
      }
      Incoming_value = 0;
      wifi_counter++;
    delay(200);
}