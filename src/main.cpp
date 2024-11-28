#include <Arduino.h>

#define WIFI_SSID "ZION"
#define WIFI_PASS "Nirvana13~"
#define MQTT_USER "denys"
#define MQTT_PASS "123456"
#define MQTT_SERVER "192.168.1.43"
#define MQTT_PORT 1883

#include "Publisher.hpp"
#include "WiFiStation.hpp"

static Publisher publisher{MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS};

static void
setupSerial(const uint32_t baud)
{
    Serial.setTimeout(2000);
    Serial.begin(baud);
    while (not Serial) {
        delay(10);
    }
    Serial.println();
    Serial.println();
}

void
setup()
{
    setupSerial(9600);

    WiFiStation::connect(WIFI_SSID, WIFI_PASS);

    publisher.connect();
}

void
loop()
{
    publisher();
}