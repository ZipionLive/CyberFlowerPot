//
// Created by Zipio on 07/03/2026.
//

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t digitalPin)
    : _digitalPin(digitalPin),
      _dht(digitalPin, DHT_TYPE) {
    _dht.begin();
}

float TemperatureSensor::readTemperature() {
    return _dht.readTemperature();
}

