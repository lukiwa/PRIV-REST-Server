#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include "WiFiConnection.h"
#include "RestfulLeds.h"
#include "RestServer.h"
#include "WiFiConnectionBuilder.h"

RestServer server;
RestfulLeds res;
void setup()
{
  Serial.begin(9600);
  WiFiConnectionBuilder builder;
  auto connection = builder.Hostname("My server").Ssid("ssid").Password("password").
                    SelectedIP(IPAddress(1, 1, 1, 1)).
                    GatewayIP(IPAddress(1, 1, 1, 1)).
                    Subnet(IPAddress(1, 1, 1, 1)).
                    Dns(IPAddress(1, 1, 1, 1)).Build();


  auto wifi_status = connection.Connect();
  if (wifi_status == WL_CONNECTED)
  {
    Serial.print("Connected to WiFi at IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {

    Serial.print("Unable to connect to WiFi, error code ");
    Serial.print(wifi_status);
    Serial.println("Exiting now...");
    exit(wifi_status);
  }

  server.Begin("/leds", res);
}

void loop()
{
  server.HandleClient();
}
