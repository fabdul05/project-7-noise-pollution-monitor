#ifndef SOUNDMONITOR_H
#define SOUNDMONITOR_H

#include <WiFi.h>
#include <WebServer.h>

class SoundServer {
public:
    SoundServer(int soundPin, int threshold);
    void begin(const char* ssid, const char* password);
    void update();

private:
    int _soundPin;
    int _threshold;

    void handleRoot();
    void handleSound();

    WebServer server{80};
};

#endif

