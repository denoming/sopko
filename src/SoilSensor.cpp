#include "SoilSensor.hpp"

static constexpr uint8_t kAnalogPin = 0;



SoilSensor::SoilSensor()
    : _updateTimer{[this] { read(); }, 3000, 0, MILLIS}
{
}

void
SoilSensor::onHumidityUpdate(OnUpdate callback)
{
    _humidity.onUpdate(std::move(callback));
}

void
SoilSensor::start()
{
    _updateTimer.start();
}

void
SoilSensor::operator()()
{
    _updateTimer.update();
}

void
SoilSensor::read()
{
    const int value = analogRead(kAnalogPin);
    _humidity.set(value);
}