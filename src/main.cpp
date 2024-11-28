#include <Arduino.h>

#include "WiFiStation.hpp"
#include "Publisher.hpp"

static Publisher publisher{SPK_MQTT_HOST, SPK_MQTT_PORT, SPK_MQTT_USER, SPK_MQTT_PASS};

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
    setupSerial(SPK_MISC_BAUD);

    WiFiStation::connect(SPK_WIFI_SSID, SPK_WIFI_PASS);

    publisher.connect();
}

void
loop()
{
    publisher();
}