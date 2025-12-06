#ifndef SOUNDMONITOR_H
#define SOUNDMONITOR_H

#include <Arduino.h>

class SoundMonitor {
public:
    SoundMonitor(int pin, int threshold);

    void begin();
    void update();  // call repeatedly inside loop()

private:
    int soundPin;
    int threshold;
    bool noiseActive;
};

#endif
