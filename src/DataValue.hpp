#pragma once

#include <string>
#include <functional>

class DataValue {
public:
    using Callback = std::function<void(const std::string& value)>;

    static inline const char* kFieldCaption = "caption";
    static inline const char* kFieldValue = "value";

    DataValue(std::string caption, std::string topic);

    virtual ~DataValue() = default;

    [[nodiscard]] const std::string&
    caption() const;

    [[nodiscard]] const std::string&
    topic() const;

    void
    onUpdate(Callback callback);

protected:
    [[nodiscard]] virtual std::string
    format()
        = 0;

    void
    notifyUpdate();

private:
    std::string _caption;
    std::string _topic;
    Callback _callback;
};