#pragma once

#include "SoilHumidityValue.hpp"

#include <TickTwo.h>

#include <string>
#include <functional>

class SoilSensor {
public:
    using OnUpdate = std::function<void(const std::string& value)>;

    SoilSensor();

    void
    onHumidityUpdate(OnUpdate callback);

    void
    start();

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