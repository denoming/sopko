#pragma once

#include "DataValue.hpp"

#include <optional>

template<typename T>
class TypedDataValue : public DataValue {
public:
    TypedDataValue(std::string caption, std::string topic)
        : DataValue{std::move(caption), std::move(topic)}
    {
    }

    void
    set(T value)
    {
        if (_value != value) {
            _value = value;
            notifyUpdate();
        }
    }

    const T&
    get() const
    {
        return *_value;
    }

    [[nodiscard]] bool
    empty() const
    {
        return _value.has_value();
    }

private:
    std::optional<T> _value{};
};