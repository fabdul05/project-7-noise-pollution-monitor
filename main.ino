#include "SoundMonitor.h"

// Replace with your WiFi credentials
const char* ssid     = "Your Wifi Name";
const char* password = "Your Wifi Password";

SoundServer soundServer(33, 1200);

void setup() {
    Serial.begin(115200);
    delay(300);

    soundServer.begin(ssid, password);
}

void loop() {
    soundServer.update();
}
