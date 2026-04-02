#include <Arduino.h>
#include "RF24Receiver.h"
#include "SensorData.h"

#define RFR_CSN_PIN 10
#define RFR_CE_PIN 9
#define RFR_CHANNEL 42

RF24Receiver receiver(RFR_CSN_PIN, RFR_CE_PIN, RFR_CHANNEL);

unsigned long lastReceiveTime = 0;
const unsigned long receiveTimeoutMs = 5000;

void printData(const SensorData& data) {
    Serial.println(F("=== Cyber Flower Pot ==="));

    Serial.print(F("Humidity : "));
    Serial.print(data.humidity);
    Serial.println(F("%"));

    Serial.print(F("Water level : "));
    Serial.print(data.waterLevel, 1);
    Serial.println(F(" cm"));

    Serial.print(F("Temperature : "));
    Serial.print(data.temperature, 2);
    Serial.println(F(" °C"));

    Serial.println();
}

void setup() {
    Serial.begin(9600);
    delay(1000);

    Serial.println(F("Boot"));

    if (!receiver.begin()) {
        Serial.println(F("RF24 initialization FAILED"));
        while (true) {
            delay(1000);
        }
    }

    Serial.println(F("RF24 ready. Waiting for data..."));
}

void loop() {
    SensorData data{};

    if (receiver.readSensorData(data)) {
        printData(data);
        lastReceiveTime = millis();
    }

    if (millis() - lastReceiveTime > receiveTimeoutMs) {
        Serial.println(F("No data received..."));
        delay(1000);
    }

    delay(100);
}