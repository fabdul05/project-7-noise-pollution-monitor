#ifndef SOUNDMONITOR_H
#define SOUNDMONITOR_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

class SoundMonitor {
public:
    SoundMonitor(int pin, int threshold);

    void begin(const char* ssid, const char* password);
    void update();

private:
    int soundPin;
    int threshold;
    bool noiseActive;
    int lastSoundValue;

    WebServer server;

    void handleSound();
    void handleState();
    void handleJSON();
};

#endif
