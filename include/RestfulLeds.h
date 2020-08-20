#pragma once
#include "LedStatus.h"
#include "RestfulResource.h"
#include "etl/vector.h"

class RestfulLeds : public RestfulResource
{
private:
    static const int MAX_LED_NUMBER{5};
    etl::vector<LedStatus, MAX_LED_NUMBER> _leds;

public:
    RestfulLeds();

    void HandleGet(ESP8266WebServer &server) const override;
    void HandleGetArgs(ESP8266WebServer &server) const override;
    void HandlePut(ESP8266WebServer &server) override;
    void HandleDelete(ESP8266WebServer &server) override;
    void HandlePost(ESP8266WebServer &server) override;

    String CreateJsonFromResource(const LedStatus *it = nullptr) const;
    bool DeserializeAndCreateLedStatus(ESP8266WebServer &server, LedStatus &out_led_status) const;
    void ModifyResource(ESP8266WebServer &server);
};
