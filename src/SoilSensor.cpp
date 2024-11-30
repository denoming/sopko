#include "SoilSensor.hpp"

#ifdef SPK_HA_INTEGRATE
#include <ArduinoJson.h>
#endif

SoilSensor::SoilSensor(Publisher& publisher, const std::chrono::milliseconds readInterval)
    : _publisher{publisher}
    , _updateTimer{[this] { read(); }, static_cast<uint32_t>(readInterval.count()), 0, MILLIS}
{
    _publisher.onConnected([this](const char* /*clientId*/) { onPublisherConnected(); });
    _publisher.onDisconnected([this]() { onPublisherDisconnected(); });
    _humidity.onUpdate([this](const std::string& topic, const std::string& value) {
        onHumidityUpdate(topic, value);
    });
}

SoilSensor::~SoilSensor()
{
    _publisher.onConnected(nullptr);
    _publisher.onDisconnected(nullptr);
}

void
SoilSensor::start()
{
    _updateTimer.start();
}

void
SoilSensor::stop()
{
    _updateTimer.stop();
}

void
SoilSensor::operator()()
{
    _updateTimer.update();
}

void
SoilSensor::read()
{
    const int value = analogRead(A0);
    _humidity.set(value);
}

void
SoilSensor::integrate()
{
    JsonDocument json;
    json["entity_category"] = "diagnostic";
    json["name"] = "sopko/Humidity";
    json["state_topic"] = _humidity.topic();
    json["value_template"] = "{{ value_json.value }}";

    std::string output;
    serializeJson(json, output);
    _publisher.publish("homeassistant/sensor/sopko/humidity/config", output);

    json.clear();
    json["entity_category"] = "diagnostic";
    json["name"] = "sopko/HumidityIndex";
    json["state_topic"] = _humidity.topic();
    json["value_template"] = "{{ value_json.index }}";

    output.clear();
    serializeJson(json, output);
    _publisher.publish("homeassistant/sensor/sopko/humidity-index/config", output);
}

void
SoilSensor::onHumidityUpdate(const std::string& topic, const std::string& value) const
{
    _publisher.publish(topic.data(), value);
}

void
SoilSensor::onPublisherConnected()
{
    start();
#ifdef SPK_HA_INTEGRATE
    integrate();
#endif
}

void
SoilSensor::onPublisherDisconnected()
{
    stop();
}