//
// Created by Zipio on 02/04/2026.
//

#ifndef SENSORDATA_H
#define SENSORDATA_H
#include <stdint.h>

struct SensorData {
    uint8_t humidity;
    float temperature;
    float waterLevel;

    SensorData() : humidity(0), temperature(0.0f), waterLevel(0.0f) {}
};

#endif //SENSORDATA_H
