#include <Arduino.h>
#include "SoilMoistureSensor.h"
#include "TemperatureSensor.h"
#include "WaterLevelSensor.h"

#define SMS_PIN A0
#define WLS_PIN A1
#define TS_PIN 2
#define WLS_HIGH_ADDR 0x78
#define WLS_LOW_ADDR 0x77

SoilMoistureSensor sms(SMS_PIN);
WaterLevelSensor wls(WLS_LOW_ADDR, WLS_HIGH_ADDR);
TemperatureSensor ts(TS_PIN);

void setup() {
    Serial.begin(9600);
}

void loop() {
    const int humidity = sms.readPercentage();
    const float temperature = ts.readTemperature();
    const float waterLevel = wls.readWaterLevel();
    Serial.write("Humidity : ");
    Serial.write(humidity);
    Serial.write(" %");
    Serial.println();
    Serial.write("Temperature : ");
    Serial.print(temperature, 2);
    Serial.write("°C");
    Serial.println();
    if (waterLevel < 0) {
        Serial.println("Water level sensor not found!");
    } else {
        Serial.write("Water level : ");
        Serial.print(waterLevel, 1);
        Serial.write(" cm");
        Serial.println();
    }

    delay(500);
}