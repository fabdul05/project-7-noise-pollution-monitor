#include "SoundMonitor.h"

SoundMonitor::SoundMonitor(int pin, int thresh)
    : soundPin(pin), threshold(thresh),
      noiseActive(false), lastSoundValue(0), server(80) {}

void SoundMonitor::begin(const char* ssid, const char* password) {
    Serial.begin(115200);
    delay(500);

    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    // API Endpoints
    server.on("/sound", std::bind(&SoundMonitor::handleSound, this));
    server.on("/state", std::bind(&SoundMonitor::handleState, this));
    server.on("/json",  std::bind(&SoundMonitor::handleJSON,  this));

    server.begin();
    Serial.println("REST API server started");
}

void SoundMonitor::handleSound() {
    server.send(200, "text/plain", String(lastSoundValue));
}

void SoundMonitor::handleState() {
    server.send(200, "text/plain", noiseActive ? "loud" : "normal");
}

void SoundMonitor::handleJSON() {
    String json = "{";
    json += "\"sound\":" + String(lastSoundValue) + ",";
    json += "\"threshold\":" + String(threshold) + ",";
    json += "\"state\":\"" + String(noiseActive ? "loud" : "normal") + "\"";
    json += "}";
    server.send(200, "application/json", json);
}

void SoundMonitor::update() {
    server.handleClient();   // handle web requests

    int soundValue = analogRead(soundPin);

    Serial.print("Sound level: ");
    Serial.println(soundValue);

    if (soundValue > threshold && !noiseActive) {
        noiseActive = true;
        Serial.println("⚠️ Noise threshold exceeded!");
    }

    if (soundValue <= threshold && noiseActive) {
        noiseActive = false;
        Serial.println("Noise back to normal.");
    }
    delay(20);
}

