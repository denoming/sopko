#include "SoilSensor.hpp"

SoilSensor::SoilSensor(std::chrono::milliseconds readInterval)
    : _updateTimer{[this] { read(); }, static_cast<uint32_t>(readInterval.count()), 0, MILLIS}
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