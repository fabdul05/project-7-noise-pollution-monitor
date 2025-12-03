#include "NoiseSensor.h"
#include <Arduino.h>
#include <math.h>

static const double REF_VOLTAGE = 3.3;
static const int ADC_MAX = 4095;

NoiseSensor::NoiseSensor(int pin) : micPin(pin) {}

int NoiseSensor::smoothRead() {
    long sum = 0;
    for (int i = 0; i < SAMPLES; i++) {
        sum += analogRead(micPin);
        delayMicroseconds(500);
    }
    return sum / SAMPLES;
}

double NoiseSensor::adcToDB(int raw) {
    double voltage = (raw / (double)ADC_MAX) * REF_VOLTAGE;
    return 20.0 * log10(voltage + 0.0001); 
}

Measurement NoiseSensor::read(const String& location) {
    int raw = smoothRead();
    double db = adcToDB(raw);

    Measurement m;
    m.timestamp_ms = millis();
    m.decibels = db;
    m.location = location;
    return m;
}
