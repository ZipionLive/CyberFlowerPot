//
// Created by Zipio on 02/04/2026.
//

#ifndef RF24RECEIVER_H
#define RF24RECEIVER_H
#include <stdint.h>
#include <RF24.h>
#include <SensorData.h>

class RF24Receiver {
public:
    explicit RF24Receiver(uint8_t chipSelectPin, uint8_t chipEnablePin, uint8_t channel);

    bool begin();
    bool readSensorData(SensorData &data);

private:
    uint8_t _channel;
    RF24 _radio;
};

#endif //RF24RECEIVER_H
