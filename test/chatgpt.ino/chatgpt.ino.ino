#include <ArduinoJson.h>
#include <WiFiManager.h>
// #include <BluetoothSerial.h>

// WiFiManager variables
WiFiManager wifiManager;

// Bluetooth variables
// BluetoothSerial SerialBT;

// Relay variables
const int relayPin1 = 2;
const int relayPin2 = 3;
const int relayPin3 = 4;
const int relayPin4 = 5;
const int relayPin5 = 6;
const int relayPin6 = 7;

// Button variables
const int wifiConfigButtonPin = 8;

// WiFi credentials
char ssid[32] = "";
char password[32] = "";

// Flag for WiFi configuration portal
bool shouldConfigWifi = false;

// Function to control the relay
void controlRelay(int relay, bool state) {
  digitalWrite(relay, state ? HIGH : LOW);
}

// WiFi configuration callback
void configModeCallback(WiFiManager *myWiFiManager) {
  shouldConfigWifi = true;
}

// Function to handle WiFi configuration
void configureWiFi() {
  // Set WiFi configuration callback
  wifiManager.setAPCallback(configModeCallback);

  // Start the configuration portal
  if (!wifiManager.autoConnect("ESP32-Relay-Config")) {
    // Failed to connect or timed out
    // Handle the error here
    // For simplicity, we'll reset the ESP32
    ESP.restart();
  }

  // If the WiFi configuration portal was requested
  if (shouldConfigWifi) {
    // Get the entered WiFi credentials
    strncpy(ssid, wifiManager.getWiFiSSID().c_str(), sizeof(ssid));
    strncpy(password, wifiManager.getWiFiPass().c_str(), sizeof(password));
  }
}

// Function to handle Bluetooth commands
void handleBluetoothCommands() {
  // while (SerialBT.available() > 0) {
  //   char command = SerialBT.read();
  while (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case '1':
        controlRelay(relayPin1, true);
        break;
      case '2':
        controlRelay(relayPin2, true);
        break;
      case '3':
        controlRelay(relayPin3, true);
        break;
      case '4':
        controlRelay(relayPin4, true);
        break;
      case '5':
        controlRelay(relayPin5, true);
        break;
      case '6':
        controlRelay(relayPin6, true);
        break;
      case 'A':
        controlRelay(relayPin1, false);
        break;
      case 'B':
        controlRelay(relayPin2, false);
        break;
      case 'C':
        controlRelay(relayPin3, false);
        break;
      case 'D':
        controlRelay(relayPin4, false);
        break;
      case 'E':
        controlRelay(relayPin5, false);
        break;
      case 'F':
        controlRelay(relayPin6, false);
        break;
    }
  }
}

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Initialize Bluetooth
  // SerialBT.begin("ESP32-Relay");

  // Set relay pins as outputs
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(relayPin6, OUTPUT);

  // Set WiFi configuration button as input
  pinMode(wifiConfigButtonPin, INPUT_PULLUP);

  // Check if the WiFi configuration button is pressed on startup
  if (digitalRead(wifiConfigButtonPin) == LOW) {
    shouldConfigWifi = true;
  }

  // Configure WiFi
  configureWiFi();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  // Check if the WiFi configuration portal is requested
  if (shouldConfigWifi) {
    configureWiFi();
    shouldConfigWifi = false;
  }

  // Handle Bluetooth commands
  handleBluetoothCommands();
}