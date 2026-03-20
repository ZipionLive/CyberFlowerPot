//
// Created by Zipio on 07/03/2026.
//

#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin) : _analogPin(analogPin) {}

int SoilMoistureSensor::readPercentage() {
    int raw = analogRead(_analogPin);

    if (raw <= 320) { raw = 320; }

    return map(raw, 1023, 320, 0, 100);
}