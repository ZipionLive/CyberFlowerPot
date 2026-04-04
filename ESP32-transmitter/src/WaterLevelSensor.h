//
// Created by Zipio on 04/04/2026.
//

#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H
#include <cstdint>

class WaterLevelSensor {
public:
    WaterLevelSensor(uint8_t i2cLowAddr, uint8_t i2cHighAddr);
    float readWaterLevel();

private:
    uint8_t _i2cLowAddr;
    uint8_t _i2cHighAddr;

    bool i2cDeviceAvailable(uint8_t addr);
    void getLow8SectionValue();
    void getHigh12SectionValue();
};

#endif //WATERLEVELSENSOR_H
