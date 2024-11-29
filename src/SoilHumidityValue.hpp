#pragma once

#include "TypedDataValue.hpp"

class SoilHumidityValue final : public TypedDataValue<int> {
public:
    static inline const char* kFieldIndex = "index";

    SoilHumidityValue();

private:
    [[nodiscard]] std::string
    format() override;
};
