#include "DataValue.hpp"

DataValue::DataValue(std::string caption, std::string topic)
    : _caption{std::move(caption)}
    , _topic{std::move(topic)}
{
}

const std::string&
DataValue::caption() const
{
    return _caption;
}

const std::string&
DataValue::topic() const
{
    return _topic;
}

void
DataValue::onUpdate(Callback callback)
{
    _callback = std::move(callback);
}

void
DataValue::notifyUpdate()
{
    if (_callback) {
        _callback(_topic, format());
    }
}
