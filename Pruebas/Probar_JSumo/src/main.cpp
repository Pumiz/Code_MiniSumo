#include <Arduino.h>
#define SensorLEFT A4 // Analog sensor connected to A4
#define SensorRIGH A5 // Analog sensor connected to A5

int value;       // We define variable for storing sensor output.
int value2;       // We define variable for storing sensor output.

void setup() {
  pinMode(SensorLEFT, INPUT); // SensorLEFT is declared as input
  pinMode(SensorRIGH, INPUT); // SensorLEFT is declared as input
  Serial.begin(9600); // Serial communication started with 9600 bits per second.
}

void loop() {
  value = analogRead(SensorLEFT);    // Sensor is read digitally
  value2 = analogRead(SensorRIGH);    // Sensor is read digitally
  Serial.print("Sensor LEFT: "); // IT will write Sensor Output to Serial
  Serial.print(value); // It will write value variable raw value (0 or 1)
  Serial.print("   Sensor RIGH:");
  Serial.println(value2);
  delay(100);            // We added 100ms Delay for more balanced readings.
}