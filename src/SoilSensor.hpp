#pragma once

#include "SoilHumidityValue.hpp"
#include "Publisher.hpp"

#include <TickTwo.h>

#include <string>
#include <functional>
#include <chrono>

class SoilSensor {
public:
    explicit SoilSensor(Publisher& publisher, std::chrono::milliseconds readInterval);

    ~SoilSensor();

    void
    start();

    void
    stop();

    void
    operator()();

private:
    void
    read();

#ifdef SPK_HA_INTEGRATE
    void
    integrate();
#endif

    void
    onHumidityUpdate(const std::string& topic, const std::string& value) const;

    void
    onPublisherConnected();

    void
    onPublisherDisconnected();

private:
    Publisher& _publisher;
    TickTwo _updateTimer;
    SoilHumidityValue _humidity;
};