//
// Created by Zipio on 21/03/2026.
//

#include "RF24Transmitter.h"
#include <Arduino.h>
#include <RF24.h>
#include <stdint.h>

RF24Transmitter::RF24Transmitter(uint8_t chipSelectPin, uint8_t chipEnablePin, uint8_t channel)
    : _channel(channel), _radio(chipEnablePin, chipSelectPin) {}

void RF24Transmitter::sendText(String text) {
    // Logic address of the transmission pipe
    // The receiver will have to use the same address
    constexpr byte address[6] = "CFP1";

    if (!_radio.begin()) {
        Serial.println("nRF24L01 not detected !");
        return;
    }

    _radio.setChannel(_channel); // RF channel from 0 to 125
    _radio.setPALevel(RF24_PA_LOW); // Reduces power consumption and minimizes power supply issues
    _radio.setDataRate(RF24_1MBPS);
    _radio.setAutoAck(false);
    _radio.openWritingPipe(address);
    _radio.stopListening();

    // Send by blocks of 32 bytes maximum
    // Save one byte for null terminator => 31 significant characters
    constexpr uint8_t chunkSize = 31;
    const size_t textLength = text.length();

    if (textLength == 0) {
        char empty[32] = {0};
        bool ok = _radio.write(&empty, sizeof(empty));
        Serial.println(ok ? "Empty text sent" : "Failed to send empty text");
        return;
    }

    for (size_t offset = 0; offset < textLength; offset += chunkSize) {
        char payload[32] = {0};

        size_t length = text.length() - offset;
        if (length > chunkSize) {
            length = chunkSize;
        }

        text.substring(offset, offset + length)
            .toCharArray(payload, sizeof(payload));
        bool ok = _radio.write(&payload, sizeof(payload));

        if (!ok) {
            Serial.print("Transmission failed at chunk starting at index ");
            Serial.println(offset);
            return;
        }
    }

    Serial.println("Text sent successfully");
}

bool RF24Transmitter::sendPayload(uint8_t* data, uint8_t size) {
    constexpr byte address[6] = "CFP1";

    if (!_radio.begin()) {
        Serial.println("nRF24L01 not detected !");
        return false;
    }

    _radio.setChannel(_channel); // RF channel from 0 to 125
    _radio.setPALevel(RF24_PA_LOW); // Reduces power consumption and minimizes power supply issues
    _radio.setDataRate(RF24_1MBPS);
    _radio.setAutoAck(false);
    _radio.openWritingPipe(address);
    _radio.stopListening();

    return _radio.write(data, size);
}


