//
// Created by Zipio on 04/04/2026.
//

#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin, int dryAdc, int wetAdc)
    : _analogPin(analogPin), _dryAdc(dryAdc), _wetAdc(wetAdc) { }

void SoilMoistureSensor::begin() {
    analogReadResolution(12);
    analogSetPinAttenuation(_analogPin, ADC_11db);
}

int SoilMoistureSensor::readRaw() const {
    return analogRead(_analogPin);
}

int SoilMoistureSensor::readPercentage() const {
    const int raw = readRaw();

    int percentage = map(raw, _dryAdc, _wetAdc, 0, 100);
    percentage = constrain(percentage, 0, 100);

    return percentage;
}
