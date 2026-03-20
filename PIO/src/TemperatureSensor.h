//
// Created by Zipio on 07/03/2026.
//

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>
#include <DHT.h>

#define DHT_TYPE DHT11

class TemperatureSensor {
public:
    // constructor | parameters : digitalPin -> pin used by the sensor
    explicit TemperatureSensor(uint8_t digitalPin);

    // Reading of the temperature
    float readTemperature();
private:
    uint8_t _digitalPin;
    DHT _dht;
};

#endif //TEMPERATURESENSOR_H
