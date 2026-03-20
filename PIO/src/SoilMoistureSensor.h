//
// Created by Zipio on 07/03/2026.
//

#ifndef SOILMOISTURESENSOR_H
#define SOILMOISTURESENSOR_H

#include <Arduino.h>

class SoilMoistureSensor {
public:
    // constructor | parameters : analogPin -> pin used by the sensor
    explicit SoilMoistureSensor(uint8_t analogPin);

    // Reading of the moisture level
    int readPercentage();
private:
    uint8_t _analogPin;
};

#endif //SOILMOISTURESENSOR_H
