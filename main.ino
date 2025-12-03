#include <Arduino.h>
#include "NoiseSensor.h"

NoiseSensor sensor(34); // pin on ESP32

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting up");
}

void loop() {
    Measurement m = sensor.read("Test Location");

    Serial.print("Timestamp(ms): ");
    Serial.print(m.timestamp_ms);
    Serial.print(" | dB: ");
    Serial.print(m.decibels);
    Serial.print(" | Location: ");
    Serial.println(m.location);

    delay(10000); 
}
