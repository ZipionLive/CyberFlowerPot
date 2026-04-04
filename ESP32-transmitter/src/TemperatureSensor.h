//
// Created by Zipio on 04/04/2026.
//

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>
#include <DHT.h>

#define DHT_TYPE DHT11

class TemperatureSensor {
public:
    explicit TemperatureSensor(uint8_t digitalPin);

    void begin();
    float readTemperature() const;

private:
    uint8_t _digitalPin;
    mutable DHT _dht;
};

#endif //TEMPERATURESENSOR_H
