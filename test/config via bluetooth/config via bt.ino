#include <BluetoothSerial.h>
#include <WiFi.h>

#define BUTTON_PIN 2

BluetoothSerial SerialBT;

// WiFi credentials
char ssid[32] = "";
char password[32] = "";

// Flag to indicate if WiFi configuration is requested
bool shouldConfigWifi = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  SerialBT.begin("ESP32_Config"); // Bluetooth device name

  // Initialize WiFi
  WiFi.mode(WIFI_STA);

  // Check if WiFi configuration button is pressed on startup
  if (digitalRead(BUTTON_PIN) == LOW) {
    shouldConfigWifi = true;
  }
}

void loop() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();

    // Check if received character is the start of WiFi credentials
    if (receivedChar == '{') {
      memset(ssid, 0, sizeof(ssid));
      memset(password, 0, sizeof(password));
      int ssidIndex = 0;
      int passwordIndex = 0;

      while (SerialBT.available()) {
        receivedChar = SerialBT.read();

        // Check if received character is the end of WiFi credentials
        if (receivedChar == '}') {
          shouldConfigWifi = true;
          break;
        }

        // Store characters in respective arrays
        if (receivedChar == '|') {
          ssidIndex = 0;
          passwordIndex = 0;
        } else if (ssidIndex < sizeof(ssid) - 1) {
          ssid[ssidIndex++] = receivedChar;
        } else if (passwordIndex < sizeof(password) - 1) {
          password[passwordIndex++] = receivedChar;
        }
      }
    }
  }

  // Check if WiFi configuration is requested
  if (shouldConfigWifi) {
    configureWiFi();
    shouldConfigWifi = false;
  }

  // Your main code goes here
}

void configureWiFi() {
  WiFi.disconnect();

  // Connect to WiFi using the provided credentials
  if (WiFi.begin(ssid, password) == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi connection failed");
  }
}