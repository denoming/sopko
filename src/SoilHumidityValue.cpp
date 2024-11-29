#include "SoilHumidityValue.hpp"

#include <ArduinoJson.h>

static std::string
getIndex(const int value)
{
    if (value >= 0 and value < 300) {
        return "DrySoil";
    }
    if (value >= 300 and value < 700) {
        return "HumidSoil";
    }
    if (value >= 700) {
        return "InWater";
    }
    return "Invalid";
}

SoilHumidityValue::SoilHumidityValue()
    : TypedDataValue{"Soil Humidity", "sopko/SoilHumidity"}
{
}

std::string
SoilHumidityValue::format()
{
    static JsonDocument json;

    const int value = get();
    json[kFieldCaption] = caption();
    json[kFieldValue] = value;
    json[kFieldIndex] = getIndex(value);

    std::string output;
    serializeJson(json, output);
    return output;
}