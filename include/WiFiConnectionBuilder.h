#pragma once

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "WiFiConnection.h"

class WiFiConnectionBuilder
{
private:
    typedef WiFiConnectionBuilder Builder;
    IPAddress _ip;
    IPAddress _gateway_ip;
    IPAddress _subnet;
    IPAddress _dns{0, 0, 0, 0};

    String _ssid;
    String _password;
    String _hostname;

public:
    Builder &Ssid(const String &ssid);
    Builder &Password(const String &password);
    Builder &Hostname(const String &hostname);
    Builder &SelectedIP(const IPAddress &ip);
    Builder &GatewayIP(const IPAddress &gateway_ip);
    Builder &Subnet(const IPAddress &subnet);
    Builder &Dns(const IPAddress &dns);
    WiFiConnection Build();
};
