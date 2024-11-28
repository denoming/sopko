#include "Publisher.hpp"

#include <ESP8266WiFi.h>

#include <functional>

Publisher::Publisher(const char* host, uint16_t port, const char* username, const char* password)
    : Publisher{}
{
    _client.setCredentials(username, password);
    _client.setServer(host, port);
}

Publisher::Publisher(const IPAddress& addr,
                     const uint16_t port,
                     const char* username,
                     const char* password)
    : Publisher{}
{
    _client.setCredentials(username, password);
    _client.setServer(addr, port);
}

Publisher::Publisher()
    : _reconnectTimer{[this] { tryConnect(); }, 3000, 0, MILLIS}
{
    _onWiFiHandler1 = WiFi.onStationModeGotIP([this](const auto&) { onHasNetwork(); });
    _onWiFiHandler2 = WiFi.onStationModeDisconnected([this](const auto&) { onLostNetwork(); });

    _client.onConnect([this](const bool hasSession) { onConnect(hasSession); });
    _client.onDisconnect([this](const auto reason) { onDisconnect(reason); });
}

Publisher::~Publisher()
{
    if (_onWiFiHandler1) {
        _onWiFiHandler1.reset();
    }
    if (_onWiFiHandler2) {
        _onWiFiHandler2.reset();
    }
}

bool
Publisher::connected() const
{
    return _client.connected();
}

void
Publisher::connect()
{
    if (WiFi.isConnected()) {
        tryConnect();
    } else {
        Serial.println("Waiting for WiFi connection");
    }
}

void
Publisher::publish(const char* topic, const char* payload, const bool retained)
{
    if (_client.connected()) {
        _client.publish(topic, 2, retained, payload, strlen(payload));
    }
}

void
Publisher::operator()()
{
    _reconnectTimer.update();
}

void
Publisher::tryConnect()
{
    if (not _client.connected()) {
        Serial.println("Connecting to MQTT");
        _client.connect();
    }
}

void
Publisher::onHasNetwork()
{
    _reconnectTimer.start();
}

void
Publisher::onLostNetwork()
{
    _reconnectTimer.stop();
}

void
Publisher::onConnect(const bool /*sessionPresent*/)
{
    Serial.print("Connected to MQTT: "), Serial.println(_client.getClientId());
    _reconnectTimer.stop();
}

void
Publisher::onDisconnect(const AsyncMqttClientDisconnectReason reason)
{
    Serial.print("Disconnected from MQTT: "), Serial.println(static_cast<int>(reason));
    if (WiFi.isConnected()) {
        _reconnectTimer.start();
    }
}
