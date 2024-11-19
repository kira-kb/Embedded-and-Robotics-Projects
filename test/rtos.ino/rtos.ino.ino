// #include <WiFi.h>
#include <WiFiManager.h>

TaskHandle_t Core1TaskHandle;

// WiFiManager variables
WiFiManager wifiManager;

// WiFi credentials
char ssid[32] = "";
char password[32] = "";

// Flag for WiFi configuration portal
bool shouldConfigWifi = false;

// LED pin numbers
const int ledPin1 = 2;
const int ledPin2 = 3;
const int BUTTON_PIN = 8;
// LED blink intervals in milliseconds
const int blinkInterval1 = 100;
const int blinkInterval2 = 500;

// Function to control the LED blink on Core 1
void core1Task(void *pvParameters) {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  while (1) {
    digitalWrite(ledPin1, HIGH);
    vTaskDelay(blinkInterval1 / portTICK_PERIOD_MS);
    digitalWrite(ledPin1, LOW);

    digitalWrite(ledPin2, HIGH);
    vTaskDelay(blinkInterval2 / portTICK_PERIOD_MS);
    digitalWrite(ledPin2, LOW);
  }
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

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Check if the WiFi configuration button is pressed on startup
  if (digitalRead(BUTTON_PIN) == LOW) {
    shouldConfigWifi = true;
  }

  // Configure WiFi
  configureWiFi();

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Create Core 1 task for LED blinking
  xTaskCreatePinnedToCore(
      core1Task, "Core1Task", 1024, NULL, 1, &Core1TaskHandle, 1);
}

void loop() {
  // Check WiFi connection every 10 seconds
  if (millis() % 10000 == 0) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected. Reconnecting...");
      WiFi.disconnect();
      WiFi.reconnect();
    }
  }

  // Check if the WiFi configuration portal is requested
  if (shouldConfigWifi) {
    configureWiFi();
    shouldConfigWifi = false;
  }
}