#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t digitalPin)
    : _digitalPin(digitalPin), _dht(digitalPin, DHT_TYPE) {
}

void TemperatureSensor::begin() {
    _dht.begin();
}

float TemperatureSensor::readTemperature() const {
    return _dht.readTemperature();
}