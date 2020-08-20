#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "RestfulResource.h"

class RestServer
{
private:
    ESP8266WebServer _esp_server;

public:
    RestServer() = default;
    ~RestServer() = default;
    void Begin(const String &endpoint, RestfulResource &resource);
    void HandleClient();
};
