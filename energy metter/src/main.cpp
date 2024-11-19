#include <Arduino.h>

// Define the analog input pin for the CT sensor
const int CT_SENSOR_PIN = A1;

// Define the calibration factor for the CT sensor
// This value will need to be adjusted based on your specific CT sensor
const float CT_SENSOR_CALIBRATION_FACTOR = 1000; // amps per millivolt

// Define the serial port for outputting data
const int SERIAL_PORT = 1;

// Define the update interval for the meter (in milliseconds)
const int UPDATE_INTERVAL = 1000;

// Declare variables to store the current and voltage readings
float currentReading;
float voltageReading;

// Declare variables to store the calculated power and energy consumption
float powerConsumption;
float energyConsumption;

// Initialize the serial port
void setup() {
  Serial.begin(SERIAL_PORT);
}

// Read the current and voltage from the CT sensor and calculate the power and energy consumption
void loop() {
  // Read the current reading from the CT sensor
  currentReading = analogRead(CT_SENSOR_PIN) / CT_SENSOR_CALIBRATION_FACTOR;

  // Read the voltage reading from the Arduino's A0 pin
  voltageReading = analogRead(A0) * 5.0 / 1023.0;

  // Calculate the power consumption
  powerConsumption = currentReading * voltageReading;

  // Calculate the energy consumption
  energyConsumption += powerConsumption * UPDATE_INTERVAL / 1000.0; // kWh

  // Output the current, voltage, power, and energy consumption to the serial port
  Serial.print("Current: ");
  Serial.print(currentReading);
  Serial.println(" A");

  Serial.print("Voltage: ");
  Serial.print(voltageReading);
  Serial.println(" V");

  Serial.print("Power: ");
  Serial.print(powerConsumption);
  Serial.println(" W");

  Serial.print("Energy: ");
  Serial.print(energyConsumption);
  Serial.println(" kWh");

  // Delay for the update interval
  delay(UPDATE_INTERVAL);
}
