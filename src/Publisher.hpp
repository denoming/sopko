#pragma once

#include <AsyncMqttClient.hpp>
#include <ESP8266WiFiGeneric.h>
#include <TickTwo.h>

#include <functional>

class Publisher {
public:
    using OnConnected = std::function<void(const char* clientId)>;
    using OnDisconnected = std::function<void()>;

    Publisher(const char* host, uint16_t port, const char* username, const char* password);

    Publisher(const IPAddress& addr, uint16_t port, const char* username, const char* password);

    ~Publisher();

    [[nodiscard]] bool
    connected() const;

    void
    connect();

    void
    onConnected(OnConnected callback);

    void
    onDisconnected(OnDisconnected callback);

    void
    publish(const char* topic, const std::string& payload, bool retained = true);

    void
    publish(const char* topic, const char* payload, size_t length = 0, bool retained = true);

    void
    operator()();

private:
    Publisher();

    void
    tryConnect();

    void
    onHasNetwork();

    void
    onLostNetwork();

    void
    onConnect(bool sessionPresent);

    void
    onDisconnect(AsyncMqttClientDisconnectReason reason);

private:
    TickTwo _reconnectTimer;
    WiFiEventHandler _onWiFiHandler1;
    WiFiEventHandler _onWiFiHandler2;
    AsyncMqttClient _client;
    OnConnected _connectedCallback;
    OnDisconnected _disconnectedCallback;
};