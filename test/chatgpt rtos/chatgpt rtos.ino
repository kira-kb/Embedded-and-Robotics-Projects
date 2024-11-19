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

// LED pin number
const int ledPin = 2;

// LED blink interval in milliseconds
const int blinkInterval = 500;

// Function to control the LED blink on Core 1
void core1Task(void *pvParameters) {
  pinMode(ledPin, OUTPUT);

  while (1) {
    digitalWrite(ledPin, HIGH);
    vTaskDelay(blinkInterval / portTICK_PERIOD_MS);
    digitalWrite(ledPin, LOW);
    vTaskDelay(blinkInterval / portTICK_PERIOD_MS);
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
  if (!wifiManager.startConfigPortal("OnDemandAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    // Reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

  // If the WiFi configuration portal was requested
  if (shouldConfigWifi) {
    // Get the entered WiFi credentials
    strncpy(ssid, wifiManager.getSSID().c_str(), sizeof(ssid));
    strncpy(password, wifiManager.getPassword().c_str(), sizeof(password));
  }
}

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Configure WiFi
  configureWiFi();

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // Create Core 1 task for LED blinking
  xTaskCreatePinnedToCore(
      core1Task, "Core1Task", 1024, NULL, 1, &Core1TaskHandle, 1);
}

void loop() {
  // Check if the WiFi configuration portal is requested
  if (shouldConfigWifi) {
    configureWiFi();
    shouldConfigWifi = false;
  }
}