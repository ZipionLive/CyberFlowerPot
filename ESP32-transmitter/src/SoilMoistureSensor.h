//
// Created by Zipio on 04/04/2026.
//

#ifndef SOILMOISTURESENSOR_H
#define SOILMOISTURESENSOR_H

#include <Arduino.h>

class SoilMoistureSensor {
public:
    explicit SoilMoistureSensor(uint8_t analogPin, int dryAdc, int wetAdc);

    void begin();
    int readRaw() const;
    int readPercentage() const;

private:
    uint8_t _analogPin;
    int _dryAdc;
    int _wetAdc;
};

#endif //SOILMOISTURESENSOR_H
