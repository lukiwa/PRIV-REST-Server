#pragma once
#include <ESP8266WebServer.h>

class RestfulResource
{
public:
    RestfulResource() = default;
    virtual ~RestfulResource() = default;

    virtual void HandleGet(ESP8266WebServer &server) const = 0;
    virtual void HandleGetArgs(ESP8266WebServer &server) const = 0;

    virtual void HandlePut(ESP8266WebServer &server) = 0;
    virtual void HandleDelete(ESP8266WebServer &server) = 0;
    virtual void HandlePost(ESP8266WebServer &server) = 0;
};
