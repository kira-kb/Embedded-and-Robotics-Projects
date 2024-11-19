// #include <FS.h> 
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

WiFiManager wifiManager;

// char Incoming_value = 0;

  HTTPClient http;

char Incoming_value = 0;

int wifi_counter = 0;

int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int led5 = 0;
int led6 = 0;

// int power;

int ans;

String httpData = "";

//flag for saving data
bool shouldSaveConfig = false;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void wifiSetup(){
  WiFi.begin(wifiManager.getWiFiSSID().c_str(), wifiManager.getWiFiPass().c_str());

  Serial.print("\n trying to connect to: ");
  Serial.println(wifiManager.getWiFiSSID());

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
  // if (WiFi.status() == WL_CONNECTED) digi;
}

void checkLedStatus() {
  
  http.begin("https://autocontrollers.000webhostapp.com/upload.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  delay(200);

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

    digitalWrite(5, led1);
    digitalWrite(18, led2);
    digitalWrite(19, led3);
    digitalWrite(21, led4);
    digitalWrite(22, led5);
    digitalWrite(23, led6);
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

void allController(char letter){
  if(WiFi.status() == WL_CONNECTED && letter == 'Z'){
    led1 = 1;
    led2 = 1;
    led3 = 1;
    led4 = 1;
    led5 = 1;
    led6 = 1;

    httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

    if (ans = http.POST(httpData) > 0){
      Serial.println("all on");
      // digitalWrite(lamp, HIGH);          
    }
  }else if(WiFi.status() != WL_CONNECTED && letter == 'Z'){
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    led5 = 0;
    led6 = 0;

    offlineController(4, 1);
    offlineController(22, 2);
    offlineController(23, 3);
    offlineController(21, 4);
    offlineController(18, 5);
    offlineController(19, 6);
  }
  else if(WiFi.status() == WL_CONNECTED && letter == 'z'){
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    led5 = 0;
    led6 = 0;

    httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

    if (ans = http.POST(httpData) > 0){
      Serial.println("all on");
      // digitalWrite(lamp, HIGH);          
    }
  }else if(WiFi.status() != WL_CONNECTED && letter == 'z'){
    led1 = 1;
    led2 = 1;
    led3 = 1;
    led4 = 1;
    led5 = 1;
    led6 = 1;

    offlineController(4, 1);
    offlineController(22, 2);
    offlineController(23, 3);
    offlineController(21, 4);
    offlineController(18, 5);
    offlineController(19, 6);
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(2, OUTPUT);  
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);

  pinMode(15, OUTPUT);

  pinMode(5, OUTPUT);
  pinMode(4, INPUT_PULLUP);

  pinMode(13, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);

  // wifiSetup();
if(WiFi.status() == WL_CONNECTED)  checkLedStatus();

  wifiManager.setSaveConfigCallback(saveConfigCallback);
  
  wifiManager.setTimeout(120);
  
  if (!wifiManager.autoConnect("AutoConnectAP", "123456789")) {
    Serial.println("failed to connect and hit timeout");
    delay(300);
    //reset and try again, or maybe put it to deep sleep
    // ESP.restart();
    // delay(5000);
    Serial.println(WiFi.localIP());
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(!digitalRead(4)) {
    // wifiManager.resetSettings();  
    digitalWrite(15, HIGH);
    if (!wifiManager.startConfigPortal("AutoConnectAP", "123456789")) {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        // ESP.restart();
        // delay(5000);
      }
      digitalWrite(15, LOW);
  }
if(WiFi.status() == WL_CONNECTED) digitalWrite(2, HIGH);
else digitalWrite(2, LOW);

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

      if(Incoming_value == 'A' || Incoming_value == 'a') sendStatus(5, 1); 

      if(Incoming_value == 'B' || Incoming_value == 'b') sendStatus(18, 2);

      if(Incoming_value == 'C' || Incoming_value == 'c')  sendStatus(19, 3); 

      if(Incoming_value == 'D' || Incoming_value == 'd')  sendStatus(21, 4);
                            
      if(Incoming_value == 'E' || Incoming_value == 'e') sendStatus(22, 5); 

      if(Incoming_value == 'F' || Incoming_value == 'f')  sendStatus(23, 6);

      if(Incoming_value == 'Z' || Incoming_value == 'z')  allController(Incoming_value);
    }
      else if (WiFi.status() != WL_CONNECTED && Incoming_value){
        if(Incoming_value == 'A' || Incoming_value == 'a') offlineController(5, 1);

        if(Incoming_value == 'B'|| Incoming_value == 'b') offlineController(18, 2);

        if(Incoming_value == 'C' || Incoming_value == 'c')  offlineController(19, 3); 

        if(Incoming_value == 'D' || Incoming_value == 'd')  offlineController(21, 4); 
                              
        if(Incoming_value == 'E' || Incoming_value == 'e') offlineController(22, 5);

        if(Incoming_value == 'F' || Incoming_value == 'f')  offlineController(23, 6);

        if(Incoming_value == 'Z' || Incoming_value == 'z')  allController(Incoming_value);

  }    

  if (WiFi.status() == WL_CONNECTED){
    if(!digitalRead(13)) sendStatus(5, 1);
    if(!digitalRead(25)) sendStatus(18, 2);
    if(!digitalRead(26)) sendStatus(19, 3);
    if(!digitalRead(27)) sendStatus(21, 4);
    if(!digitalRead(32)) sendStatus(22, 5);
    if(!digitalRead(33)) sendStatus(23, 6);
    
    checkLedStatus();
    }else {
      if(!digitalRead(13)) offlineController(5, 1);
      if(!digitalRead(25)) offlineController(18, 2);
      if(!digitalRead(26)) offlineController(19, 3);
      if(!digitalRead(27)) offlineController(21, 4);
      if(!digitalRead(32)) offlineController(22, 5);
      if(!digitalRead(33)) offlineController(23, 6);
      // wifiSetup();
      }    
      Incoming_value = 0;
      if (WiFi.status() != WL_CONNECTED) wifi_counter++;
    delay(500);
}