#include <Arduino.h>
#include <Wire.h>

#include "AppConfig.h"
#include "SensorPayload.h"
#include "SoilMoistureSensor.h"
#include "TemperatureSensor.h"
#include "WaterLevelSensor.h"
#include "WiFiTelemetryClient.h"

SoilMoistureSensor soilMoistureSensor(
    SOIL_MOISTURE_PIN,
    SOIL_ADC_DRY,
    SOIL_ADC_WET
);

TemperatureSensor temperatureSensor(TEMPERATURE_PIN);

WaterLevelSensor waterLevelSensor(
    WATER_SENSOR_LOW_ADDR,
    WATER_SENSOR_HIGH_ADDR
);

WiFiTelemetryClient telemetryClient(
    WIFI_SSID,
    WIFI_PASSWORD,
    API_URL,
    DEVICE_NAME
);

unsigned long previousMillis = 0;

static void printPayload(const SensorPayload& payload) {
    Serial.println("=== Cyber Flower Pot ===");

    Serial.print("Humidity: ");
    Serial.print(payload.humidity);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(payload.temperature, 2);
    Serial.println(" C");

    Serial.print("Water level: ");
    Serial.print(payload.waterLevel, 2);
    Serial.println(" cm");

    Serial.println();
}

static SensorPayload readSensors() {
    SensorPayload payload{};

    payload.humidity = static_cast<uint8_t>(soilMoistureSensor.readPercentage());
    payload.temperature = temperatureSensor.readTemperature();
    payload.waterLevel = waterLevelSensor.readWaterLevel();

    return payload;
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Booting ESP32 transmitter...");

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    soilMoistureSensor.begin();
    temperatureSensor.begin();

    telemetryClient.begin();

    Serial.println("Setup complete.");
}

void loop() {
    const unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= SEND_INTERVAL_MS) {
        previousMillis = currentMillis;

        const SensorPayload payload = readSensors();
        printPayload(payload);

        const bool ok = telemetryClient.sendPayload(payload, currentMillis);

        if (!ok) {
            Serial.println("Failed to send payload");
        } else {
            Serial.println("Payload sent successfully");
        }
    }

    delay(50);
}