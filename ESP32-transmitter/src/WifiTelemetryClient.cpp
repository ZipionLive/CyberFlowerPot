#include "WiFiTelemetryClient.h"
#include <HTTPClient.h>

WiFiTelemetryClient::WiFiTelemetryClient(
    const char* ssid,
    const char* password,
    const char* apiUrl,
    const char* deviceName
)
    : _ssid(ssid),
      _password(password),
      _apiUrl(apiUrl),
      _deviceName(deviceName) {
}

void WiFiTelemetryClient::begin() {
    WiFi.mode(WIFI_STA);
    connectToWiFi();
}

bool WiFiTelemetryClient::ensureConnected() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }

    Serial.println("WiFi disconnected. Reconnecting...");
    return connectToWiFi();
}

bool WiFiTelemetryClient::connectToWiFi() {
    WiFi.begin(_ssid, _password);

    Serial.print("Connecting to WiFi");
    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection failed");
        return false;
    }

    Serial.print("WiFi connected. IP: ");
    Serial.println(WiFi.localIP());

    return true;
}

String WiFiTelemetryClient::buildJson(const SensorPayload& payload, unsigned long uptimeMs) const {
    String json = "{";
    json += "\"device\":\"" + String(_deviceName) + "\",";
    json += "\"humidity\":" + String(payload.humidity) + ",";
    json += "\"temperature\":" + String(payload.temperature, 2) + ",";
    json += "\"waterLevel\":" + String(payload.waterLevel, 2) + ",";
    json += "\"uptimeMs\":" + String(uptimeMs);
    json += "}";

    return json;
}

bool WiFiTelemetryClient::sendPayload(const SensorPayload& payload, unsigned long uptimeMs) {
    if (!ensureConnected()) {
        return false;
    }

    HTTPClient http;
    http.begin(_apiUrl);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);

    const String json = buildJson(payload, uptimeMs);
    const int httpCode = http.POST(json);

    Serial.print("HTTP POST => ");
    Serial.println(httpCode);

    if (httpCode > 0) {
        const String response = http.getString();
        if (!response.isEmpty()) {
            Serial.print("Response: ");
            Serial.println(response);
        }
    } else {
        Serial.print("HTTP error: ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();

    return httpCode >= 200 && httpCode < 300;
}