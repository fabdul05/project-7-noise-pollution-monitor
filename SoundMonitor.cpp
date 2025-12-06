#include "SoundMonitor.h"

SoundMonitor::SoundMonitor(int pin, int thresh)
    : soundPin(pin), threshold(thresh), noiseActive(false) {}

void SoundMonitor::begin() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Noise event monitor started...");
}

void SoundMonitor::update() {
    int soundValue = analogRead(soundPin);

    Serial.print("Sound level: ");
    Serial.println(soundValue);

    // Noise crosses above threshold
    if (soundValue > threshold && !noiseActive) {
        noiseActive = true;
        Serial.println("⚠️ Noise threshold exceeded!");
    }

    // Noise returns below threshold
    if (soundValue <= threshold && noiseActive) {
        noiseActive = false;
        Serial.println("Noise back to normal.");
    }

    delay(10);
}
