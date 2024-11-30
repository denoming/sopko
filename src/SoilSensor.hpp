#pragma once

#include "SoilHumidityValue.hpp"

#include <TickTwo.h>

#include <string>
#include <functional>
#include <chrono>

class SoilSensor {
public:
    using OnUpdate = std::function<void(const std::string& topic, const std::string& value)>;

    explicit SoilSensor(std::chrono::milliseconds readInterval);

    void
    onHumidityUpdate(OnUpdate callback);

    void
    start();

    void
    stop();

    void
    operator()();

private:
    void
    read();

private:
    TickTwo _updateTimer;
    OnUpdate _humidityCallback;
    SoilHumidityValue _humidity;
};