#pragma once

#include <AsyncMqttClient.hpp>
#include <ESP8266WiFiGeneric.h>
#include <TickTwo.h>

class Publisher {
public:
    Publisher(const char* host, uint16_t port, const char* username, const char* password);

    Publisher(const IPAddress& addr, uint16_t port, const char* username, const char* password);

    ~Publisher();

    [[nodiscard]] bool
    connected() const;

    void
    connect();

    void
    publish(const char* topic, const char* payload, bool retained = true);

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
};