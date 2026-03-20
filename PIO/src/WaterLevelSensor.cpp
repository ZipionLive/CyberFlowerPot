//
// Created by Zipio on 07/03/2026.
//

#include <Arduino.h>
#include <Wire.h>
#include "WaterLevelSensor.h"

#define NO_TOUCH 0xFE
#define THRESHOLD 100

uint8_t lowData[8] = {0};
uint8_t highData[12] = {0};

WaterLevelSensor::WaterLevelSensor(const uint8_t i2cLowAddr, const uint8_t i2cHighAddr) {
    _i2cLowAddr = i2cLowAddr;
    _i2cHighAddr = i2cHighAddr;

    Wire.begin();
}

float WaterLevelSensor::readWaterLevel() {
    // Check if both internal I²C devices are available
    if (!i2cDeviceAvailable(_i2cLowAddr) || !i2cDeviceAvailable(_i2cHighAddr)) {
        return -1.0f;
    }

    getLow8SectionValue();
    getHigh12SectionValue();

    uint32_t raw = 0;

    // Build the 20bit touched-sections mask
    for (uint8_t i = 0; i < 8; i++) {
        if (lowData[i] > THRESHOLD) {
            raw |= (1UL << i);
        }
    }
    for (uint8_t i = 0; i < 12; i++) {
        if (highData[i] > THRESHOLD) {
            raw |= (1UL << (8 + i));
        }
    }

    // Count consecutive sections in contact with water, from the bottom
    uint8_t trigSection = 0;
    while (raw & 0x01UL) {
        trigSection++;
        raw >>= 1;
    }

    // 20 sections for 10cm => 1 section = 0.5cm
    return trigSection * 0.5f;
}

bool WaterLevelSensor::i2cDeviceAvailable(uint8_t addr) {
    Wire.beginTransmission(addr);
    return Wire.endTransmission() == 0;
}

void WaterLevelSensor::getHigh12SectionValue()
{
    memset(highData, 0, sizeof(highData));
    Wire.requestFrom(_i2cHighAddr, static_cast<uint8_t>(12));
    while (12 != Wire.available()) { }

    for (int i = 0; i < 12; i++) {
        highData[i] = Wire.read();
    }
    delay(10);
}

void WaterLevelSensor::getLow8SectionValue()
{
    memset(lowData, 0, sizeof(lowData));
    Wire.requestFrom(_i2cLowAddr, static_cast<uint8_t>(8));
    while (8 != Wire.available()) { }

    for (int i = 0; i < 8 ; i++) {
        lowData[i] = Wire.read(); // receive a byte as character
    }
    delay(10);
}
