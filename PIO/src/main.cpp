#include <Arduino.h>

#include "RF24Transmitter.h"
#include "SoilMoistureSensor.h"
#include "TemperatureSensor.h"
#include "WaterLevelSensor.h"
#include "SensorPayload.h"

#define SMS_PIN A0
#define TS_PIN 2
#define WLS_HIGH_ADDR 0x78
#define WLS_LOW_ADDR 0x77
#define RFT_CSN_PIN 10
#define RFT_CE_PIN 9
#define RFT_CHANNEL 42

SoilMoistureSensor sms(SMS_PIN);
WaterLevelSensor wls(WLS_LOW_ADDR, WLS_HIGH_ADDR);
TemperatureSensor ts(TS_PIN);
RF24Transmitter rft(RFT_CSN_PIN, RFT_CE_PIN, RFT_CHANNEL);

unsigned long previousMillis = 0;
const unsigned long interval = 500;
char buffer[32];

void sendPayload() {
    SensorPayload payload{};

    payload.humidity = sms.readPercentage();
    payload.temperature = ts.readTemperature();
    payload.waterLevel = wls.readWaterLevel();

    bool ok = rft.sendPayload((uint8_t*)&payload, sizeof(payload));

    if (!ok) {
        Serial.println("Failed to send payload");
    }

    Serial.print("H:");
    Serial.print(payload.humidity);
    Serial.print(" T:");
    Serial.print(payload.temperature, 2);
    Serial.print(" W:");
    Serial.println(payload.waterLevel, 1);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis += interval;
        sendPayload();
    }
}