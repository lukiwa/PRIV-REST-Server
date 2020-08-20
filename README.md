# PRIV-NodeMCU-REST-Server
ESP8266Webserver on NodeMCU working as a simple server for REST API purposes. Programming in C++ using Platform.IO IDE. ArduinoJson library is used for serialization and deserialization purposes. Using Embedded Template Library as a STL containers alternative.

## Usage:
* GET 
  * x.x.x.x/leds - gets all the leds.
  * x.x.x.x/leds?id= <<id>> - gets id with given id.
  * x.x.x.x/leds?gpio_pin=<<pin>> - gets led on given GPIO pin.
* DELETE
  * x.x.x.x/leds?id=<<id>> - deletes led with given id.
* PUT
  * x.x.x.x/leds + JSON body of format:
  {
      "id": 1,
      "gpio_pin": 1,
      "is_on": true
  }
  causes adding a new led
  * x.x.x.x/leds?id=<<id>> + JSON body of format:
  {
      "id": 1,
      "gpio_pin": 1,
      "is_on": true
  }
  causes modyfing a led of given id.
