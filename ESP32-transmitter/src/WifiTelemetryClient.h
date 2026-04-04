#ifndef WIFI_TELEMETRY_CLIENT_H
#define WIFI_TELEMETRY_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include "SensorPayload.h"

class WiFiTelemetryClient {
public:
    explicit WiFiTelemetryClient(
        const char* ssid,
        const char* password,
        const char* apiUrl,
        const char* deviceName
    );

    void begin();
    bool ensureConnected();
    bool sendPayload(const SensorPayload& payload, unsigned long uptimeMs);

private:
    const char* _ssid;
    const char* _password;
    const char* _apiUrl;
    const char* _deviceName;

    bool connectToWiFi();
    String buildJson(const SensorPayload& payload, unsigned long uptimeMs) const;
};

#endif