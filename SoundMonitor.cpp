#include "SoundMonitor.h"

int currentSoundValue = 0;
unsigned long lastWebUpdate = 0;
const unsigned long WEB_UPDATE_INTERVAL = 10;
int filteredValue = 0;
int lastGoodValue = 0;

SoundServer::SoundServer(int soundPin, int threshold)
    : _soundPin(soundPin), _threshold(threshold) {}

void SoundServer::begin(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // Setup HTTP routes
    server.on("/",    [this]() { handleRoot(); });
    server.on("/sound", [this]() { handleSound(); });

    server.begin();
}

void SoundServer::update() {
    currentSoundValue = analogRead(_soundPin);

    Serial.print("Sound level: ");
    Serial.println(currentSoundValue);
    static bool hasGoodValue = false;

    if (!hasGoodValue) {
        if (currentSoundValue > 0) {
            lastGoodValue = currentSoundValue;
            filteredValue = currentSoundValue;
            hasGoodValue = true;
        }
    } else {
        if (currentSoundValue > 0) {
            lastGoodValue = currentSoundValue;
            filteredValue = currentSoundValue;
        } else {
            filteredValue = lastGoodValue;
        }
    }
    server.handleClient();
}

void SoundServer::handleRoot() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "ESP32 Sound Sensor API");
}

void SoundServer::handleSound() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    unsigned long now = millis();
    if (now - lastWebUpdate < WEB_UPDATE_INTERVAL) {
        server.send(200, "text/plain", String(currentSoundValue));
        return;
    }

    lastWebUpdate = now;
    server.send(200, "text/plain", String(currentSoundValue));
}

