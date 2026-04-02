//
// Created by Zipio on 02/04/2026.
//

#include "RF24Receiver.h"
#include "SensorPayload.h"
#include <Arduino.h>
#include <nRF24L01.h>
#include <SPI.h>

RF24Receiver::RF24Receiver(uint8_t chipSelectPin, uint8_t chipEnablePin, uint8_t channel)
    : _channel(channel), _radio(chipEnablePin, chipSelectPin) { }

bool RF24Receiver::begin() {
    constexpr byte address[6] = "CFP1";

    if (!_radio.begin()) {
        Serial.println("nRF24L01 not detected!");
        return false;
    }

    _radio.setChannel(_channel);
    _radio.setPALevel(RF24_PA_LOW);
    _radio.setDataRate(RF24_1MBPS);
    _radio.setAutoAck(false);
    _radio.openReadingPipe(1, address);
    _radio.startListening();

    Serial.println("RF24 receiver ready.");
    return true;
}

bool RF24Receiver::readSensorData(SensorData &data) {
    if (!_radio.available()) {
        return false;
    }

    SensorPayload payload { };
    _radio.read(&payload, sizeof(payload));

    data.humidity = payload.humidity;
    data.temperature = payload.temperature;
    data.waterLevel = payload.waterLevel;

    return true;
}
