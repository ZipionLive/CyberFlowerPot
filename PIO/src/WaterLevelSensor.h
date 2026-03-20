//
// Created by Zipio on 07/03/2026.
//

#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

class WaterLevelSensor {
public:
    // constructor
    explicit WaterLevelSensor(uint8_t i2cLowAddr, uint8_t i2cHighAddr);

    // reading of the water level, returns -1 if no sensor found on the I²C bus.
    float readWaterLevel();
private:
    uint8_t _i2cLowAddr;
    uint8_t _i2cHighAddr;

    void getHigh12SectionValue();
    void getLow8SectionValue();
    bool i2cDeviceAvailable(uint8_t addr);
};

#endif //WATERLEVELSENSOR_H
