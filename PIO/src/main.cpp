#include <Arduino.h>

#include "RF24Transmitter.h"
#include "SoilMoistureSensor.h"
#include "TemperatureSensor.h"
#include "WaterLevelSensor.h"

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

void sendHumidity() {
    const int humidity = sms.readPercentage();
    const String s { sprintf(buffer, "[HUM]%d", humidity) };
    rft.sendText(s);
    // Serial.write("Humidity : ");
    // Serial.write(humidity);
    // Serial.write("%");
    // Serial.println();
}

void sendTemperature() {
    const float temperature = ts.readTemperature();
    const String s { sprintf(buffer, "[TMP]%.2f", temperature) };
    rft.sendText(s);
    // Serial.write("Temperature : ");
    // Serial.print(temperature, 2);
    // Serial.write("°C");
    // Serial.println();
}

void sendWaterLevel() {
    const float waterLevel = wls.readWaterLevel();
    const String s { sprintf(buffer, "[WLV]%.1f", waterLevel) };
    rft.sendText(s);
    // if (waterLevel < 0) {
    //     Serial.println("Water level sensor not found!");
    // } else {
    //     Serial.write("Water level : ");
    //     Serial.print(waterLevel, 1);
    //     Serial.write("cm");
    //     Serial.println();
    // }
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis += interval;

        sendHumidity();
        sendTemperature();
        sendWaterLevel();
    }
}