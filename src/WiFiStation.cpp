#include "WiFiStation.hpp"

#include <ESP8266WiFi.h>

static WiFiEventHandler handler1;
static WiFiEventHandler handler2;
static WiFiEventHandler handler3;

namespace WiFiStation {

static void
printScanResult(const int networksFound)
{
    Serial.printf("%d network(s) found\n", networksFound);
    for (int i = 0; i < networksFound; i++) {
        Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n",
                      i + 1,
                      WiFi.SSID(i).c_str(),
                      WiFi.channel(i),
                      WiFi.RSSI(i),
                      WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
    }
}

static void
onStationConnected(const String& ssid)
{
    Serial.print("Connected to WiFi: "), Serial.println(ssid);
    WiFi.setAutoReconnect(true);
}

static void
onStationDisconnected(const String& ssid)
{
    Serial.print("Disconnected from WiFi: "), Serial.println(ssid);
}

static void
onStationGotIp(const IPAddress& ip)
{
    Serial.print("Got IP address: "), Serial.println(ip);
}

void
listNetworks()
{
    int8_t n{};
    do {
        Serial.print("Scan WiFi networks...");
        n = WiFi.scanNetworks();
        if (n < 0) {
            Serial.println("NOK");
            delay(1000);
        } else {
            Serial.println("OK");
            printScanResult(n);
        }
    }
    while (n < 0);
}

void
connect(const char* ssid, const char* pass)
{
    if (WiFi.isConnected()) {
        WiFi.disconnect(false, true);
    }

    if (not handler1) {
        handler1 = WiFi.onStationModeConnected(
            [](const WiFiEventStationModeConnected& event) { onStationConnected(event.ssid); });
    }
    if (not handler2) {
        handler2
            = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event) {
                  onStationDisconnected(event.ssid);
              });
    }
    if (not handler3) {
        handler3 = WiFi.onStationModeGotIP(
            [](const WiFiEventStationModeGotIP& event) { onStationGotIp(event.ip); });
    }

    if (WiFi.getMode() != WIFI_STA) {
        if (not WiFi.mode(WIFI_STA)) {
            Serial.println("Error on set STA mode");
            return;
        }
    }

    WiFi.begin(ssid, pass);
}

} // namespace WiFiStation
