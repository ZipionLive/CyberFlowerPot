#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

// =========================
// WiFi / Backend
// =========================
static const char* WIFI_SSID = "NewEve-wifi";
static const char* WIFI_PASSWORD = "11Eve40re";
static const char* API_URL = "http://10.23.163.236:8080/";
static const char* DEVICE_NAME = "CFP1";

// =========================
// ESP32 pins
// =========================
// Humidity sensor: ADC pin on ESP32
static constexpr uint8_t SOIL_MOISTURE_PIN = 34;

// DHT11
static constexpr uint8_t TEMPERATURE_PIN = 4;

// I2C water level sensor
static constexpr uint8_t I2C_SDA_PIN = 21;
static constexpr uint8_t I2C_SCL_PIN = 22;
static constexpr uint8_t WATER_SENSOR_LOW_ADDR = 0x77;
static constexpr uint8_t WATER_SENSOR_HIGH_ADDR = 0x78;

// =========================
// Timing
// =========================
static constexpr unsigned long SEND_INTERVAL_MS = 5000;

// =========================
// Soil moisture calibration
// IMPORTANT:
// - SOIL_ADC_DRY = raw ADC when sensor is dry
// - SOIL_ADC_WET = raw ADC when sensor is in water / very wet soil
// You will almost certainly need to calibrate these values.
// =========================
static constexpr int SOIL_ADC_DRY = 3000;
static constexpr int SOIL_ADC_WET = 1300;

#endif