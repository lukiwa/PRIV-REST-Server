#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>

class WiFiConnection
{
private:
    static const int WIFI_RETRY_DELAY{500};
    static const int MAX_WIFI_INIT_RETRY{50};

    String _ssid;
    String _password;
    String _hostname;

    IPAddress _ip;
    IPAddress _gateway_ip;
    IPAddress _subnet;
    IPAddress _dns;

public:
    WiFiConnection(const String &ssid, const String &password, const String &hostname,
                   const IPAddress &ip, const IPAddress &gateway_ip,
                   const IPAddress &subnet, const IPAddress &dns);

    int Connect();
};
