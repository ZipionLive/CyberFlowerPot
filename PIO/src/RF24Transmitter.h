//
// Created by Zipio on 21/03/2026.
//

#ifndef RF24TRANSMITTER_H
#define RF24TRANSMITTER_H
#include <stdint.h>
#include <RF24.h>

class RF24Transmitter {
public:
    explicit RF24Transmitter(uint8_t chipSelectPin, uint8_t chipEnablePin, uint8_t channel);
    void sendText(String text);
private:
    uint8_t _channel;
    RF24 _radio;
};

#endif //RF24TRANSMITTER_H
