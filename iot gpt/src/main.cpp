#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <LittleFS.h>

const String deviceName = "deviceThree";

#define FORMAT_LITTLEFS_IF_FAILED true

TaskHandle_t nearbyTask = NULL;

WiFiManager wifiManager;

// WiFiClient client;

HTTPClient http;

boolean notConnected = true;
boolean hasInternetAccess = true;

const int portalTrigerPin = 13;
const int wifiSignalLED = 2;
const int portalSignalLED = 5;

// for bluetooth
char incoming;

// for config file
char configData[100] = "";
String input = "";

// IR Remote
const uint16_t irRecvPin = 35;

IRrecv irrecv(irRecvPin);

decode_results results;

unsigned long prevTime = millis();

// Number of buttons and LEDs.
const uint8_t NUM_LEDS = 6;

// // LEDs
// int LED1 = 4;
// int LED2 = 18;
// int LED3 = 19;
// int LED4 = 21;
// int LED5 = 22;
// int LED6 = 23;

// // buttons
// int BTN1 = 12;
// int BTN2 = 14;
// int BTN3 = 27;
// int BTN4 = 26;
// int BTN5 = 25;
// int BTN6 = 33;

// BUTTONs
int BTN1 = 4;
int BTN2 = 18;
int BTN3 = 19;
int BTN4 = 21;
int BTN5 = 22;
int BTN6 = 23;

// LEDs
int LED1 = 12;
int LED2 = 14;
int LED3 = 27;
int LED4 = 26;
int LED5 = 25;
int LED6 = 33;

struct Info
{
  const int buttonPin;
  const int ledPin;
};
Info INFOS[NUM_LEDS] = {
    {BTN1, LED1},
    {BTN2, LED2},
    {BTN3, LED3},
    {BTN4, LED4},
    {BTN5, LED5},
    {BTN6, LED6},
};

bool onSend = false;
String status;

// Function to monitor heap memory
void monitorMemory()
{
  static unsigned long lastMemCheck = 0;
  if (millis() - lastMemCheck > 5000)
  { // Check every 5 seconds
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
    lastMemCheck = millis();
  }
}

// Function to read config file
void readFile(fs::FS &fs, const char *path)
{
  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    Serial.println("- failed to open file for reading");
    return;
  }

  status = "";
  while (file.available())
  {
    status += (char)file.read();
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  // void writeFile(fs::FS &fs, const char * path, String message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("- file written");
  }
  else
  {
    Serial.println("- write failed");
  }
  file.close();
}

void sendLEDStatus()
{
  if (notConnected)
    return;
  onSend = true;
  int led1 = digitalRead(LED1);
  int led2 = digitalRead(LED2);
  int led3 = digitalRead(LED3);
  int led4 = digitalRead(LED4);
  int led5 = digitalRead(LED5);
  int led6 = digitalRead(LED6);
  String httpData = "led1=" + String(led1) + "&led2=" + String(led2) + "&led3=" + String(led3) + "&led4=" + String(led4) + "&led5=" + String(led5) + "&led6=" + String(led6);

  // Serial.println(httpData);

  String ans = "";
  if (ans = http.POST(httpData) > 0)
  {
    // Serial.print("http code");
    // Serial.print(String(led1) + ": ");
    Serial.println(ans);
  }
  onSend = false;
}

void checkLEDStatus()
{
  if (notConnected || onSend)
    return;
  String url = "http://192.168.12.187/iotAutomate/upload.php?deviceName=";
  url += deviceName;

  http.begin(url);
  // http.begin("http://192.168.215.17/iotAutomate/upload.php?deviceName=deviceThree");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  delay(100);

  if (http.GET() == 200)
  {
    String input = http.getString();

    Serial.println(input);

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, input);

    if (error)
    {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    String deviceStatus = doc["status"];

    if (!deviceStatus)
      return;

    if (status != deviceStatus)
    {
      writeFile(LittleFS, "/config.txt", deviceStatus.c_str());
      readFile(LittleFS, "/config.txt");
    }

    if (status != "active")
      return;

    int led1Status = int(doc["led1"]);
    int led2Status = int(doc["led2"]);
    int led3Status = int(doc["led3"]);
    int led4Status = int(doc["led4"]);
    int led5Status = int(doc["led5"]);
    int led6Status = int(doc["led6"]);

    // Serial.println(deviceStatus);
    // Serial.println(status);

    digitalWrite(LED1, led1Status);
    digitalWrite(LED2, led2Status);
    digitalWrite(LED3, led3Status);
    digitalWrite(LED4, led4Status);
    digitalWrite(LED5, led5Status);
    digitalWrite(LED6, led6Status);
  }
}

// Task to handle Wi-Fi connections (simplified)
void handleWifiConnection(void *parameter)
{
  for (;;)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      notConnected = false;

      digitalWrite(wifiSignalLED, HIGH);

      // if (client.connect("http://192.168.8.100/iotAutomate/upload.php", 80)) hasInternetAccess = true;
      // else hasInternetAccess = false;
      // client.stop();

      checkLEDStatus();
    }
    else
    {
      notConnected = true;
      // Serial.println("wifi not connected!!");
      digitalWrite(wifiSignalLED, LOW);

      if (wifiManager.getWiFiSSID().c_str() && wifiManager.getWiFiPass().c_str())
        WiFi.begin(wifiManager.getWiFiSSID().c_str(), wifiManager.getWiFiPass().c_str());
    }

    if (!digitalRead(portalTrigerPin))
    {
      vTaskDelay(3000 / portTICK_PERIOD_MS);
      if (!digitalRead(portalTrigerPin))
      {
        digitalWrite(portalSignalLED, HIGH);

        wifiManager.setConfigPortalTimeout(120);
        if (!wifiManager.startConfigPortal("AutoConnectAP", "123456789"))
        {
          Serial.println("failed to connect and hit timeout");
        }
        digitalWrite(portalSignalLED, LOW);
      }
    }

    // monitorMemory(); // Added memory monitor here
    // delay(500);      // Delay to avoid overwhelming the processor
    vTaskDelay(500 / portTICK_PERIOD_MS); // Delay to avoid overwhelming the processor
  }
}

// Task to handle IR communication (simplified)
void handleNearbyCommunication(void *parameters)
{
  for (;;)
  {

    // if (status != "active") {
    //   Serial.println("please activate your device");
    //   break;
    // };
    // handling bluetooth #00f
    if (Serial2.available())
    {
      incoming = Serial2.read();
      Serial2.write(incoming);

      switch (incoming)
      {
      // ON #fff
      case 'A':
        digitalWrite(LED1, HIGH);
        sendLEDStatus();
        break;
      case 'B':
        digitalWrite(LED2, HIGH);
        sendLEDStatus();
        break;
      case 'C':
        digitalWrite(LED3, HIGH);
        sendLEDStatus();
        break;
      case 'D':
        digitalWrite(LED4, HIGH);
        sendLEDStatus();
        break;
      case 'E':
        digitalWrite(LED5, HIGH);
        sendLEDStatus();
        break;
      case 'F':
        digitalWrite(LED6, HIGH);
        sendLEDStatus();
        break;
      case 'Z':
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, HIGH);
        sendLEDStatus();
        break;

        // OFF #FFF
      case 'a':
        digitalWrite(LED1, LOW);
        sendLEDStatus();
        break;
      case 'b':
        digitalWrite(LED2, LOW);
        sendLEDStatus();
        break;
      case 'c':
        digitalWrite(LED3, LOW);
        sendLEDStatus();
        break;
      case 'd':
        digitalWrite(LED4, LOW);
        sendLEDStatus();
        break;
      case 'e':
        digitalWrite(LED5, LOW);
        sendLEDStatus();
        break;
      case 'f':
        digitalWrite(LED6, LOW);
        sendLEDStatus();
        break;
      case 'z':
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);

        sendLEDStatus();
        break;
      }
      // monitorMemory();
    }

    // handling buttons #00f
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (!digitalRead(INFOS[i].buttonPin))
      {
        delay(100);
        if (digitalRead(INFOS[i].buttonPin))
        {
          digitalWrite(INFOS[i].ledPin, !digitalRead(INFOS[i].ledPin));

          // monitorMemory();
          sendLEDStatus();
        }
      }
    }

    // handling IR Remote #00f
    // unsigned long currentTime = millis();

    // if (currentTime - prevTime > 100)
    // {
    if (irrecv.decode(&results))
    {
      switch (results.value)
      {
      case 0xD671807F:
        digitalWrite(LED1, !digitalRead(LED1));
        sendLEDStatus();
        break;

      case 0xD67140BF:
        digitalWrite(LED2, !digitalRead(LED2));
        sendLEDStatus();
        break;

      case 0xD671C03F:
        digitalWrite(LED3, !digitalRead(LED3));
        sendLEDStatus();
        break;

      case 0xD67120DF:
        digitalWrite(LED4, !digitalRead(LED4));
        sendLEDStatus();
        break;

      case 0xD671A05F:
        digitalWrite(LED5, !digitalRead(LED5));
        sendLEDStatus();
        break;

      case 0xD671609F:
        digitalWrite(LED6, !digitalRead(LED6));
        sendLEDStatus();
        break;
      }
      irrecv.resume();
      // monitorMemory();
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // delay(100);
  }
  // }
}

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the IR receiver

  // Initialize Wi-Fi
  wifiManager.setConfigPortalTimeout(1);
  if (!wifiManager.autoConnect("AutoConnectAP", "123456789"))
  {
    Serial.println("Wi-Fi auto-connect failed");
  }

  // Initialize LittleFS
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
  {
    Serial.println("LittleFS Mount Failed");
    return;
  }
  readFile(LittleFS, "/config.txt");

  // Initialize pins
  pinMode(wifiSignalLED, OUTPUT);
  pinMode(portalSignalLED, OUTPUT);
  pinMode(portalTrigerPin, INPUT_PULLUP);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(INFOS[i].ledPin, OUTPUT);
    pinMode(INFOS[i].buttonPin, INPUT_PULLUP);
  }

  // Create tasks
  xTaskCreate(handleWifiConnection, "handleWifiConnection", 4096, NULL, 1, NULL);
  xTaskCreate(handleNearbyCommunication, "handleNearbyCommunication", 2048, NULL, 1, &nearbyTask);

  monitorMemory(); // Check memory after setup
}

void loop()
{
  if (status != "active" && nearbyTask != NULL)
  {
    Serial.println("Device inactive");
    vTaskSuspend(nearbyTask);
  }
  else if (status == "active")
  {
    vTaskResume(nearbyTask);
  }

  monitorMemory();                      // Periodically check memory
  vTaskDelay(100 / portTICK_PERIOD_MS); // Avoid tight loop
}