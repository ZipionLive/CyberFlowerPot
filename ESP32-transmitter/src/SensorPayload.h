//
// Created by Zipio on 04/04/2026.
//

#ifndef SENSORPAYLOAD_H
#define SENSORPAYLOAD_H

#include <stdint.h>

struct SensorPayload {
    uint8_t humidity;
    float temperature;
    float waterLevel;
};

#endif //SENSORPAYLOAD_H
