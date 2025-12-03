#pragma once
#include <Arduino.h>
#include "Measurement.h"

class NoiseSensor {
public:
    explicit NoiseSensor(int pin);
    Measurement read(const String& location);
private:
    int smoothRead();
    double adcToDB(int raw);

    int micPin;
    static const int SAMPLES = 200;
};
