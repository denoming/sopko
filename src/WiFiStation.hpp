#pragma once

namespace WiFiStation {

void
listNetworks();

void
connect(const char* ssid, const char* passphrase);

} // namespace WiFiStation
