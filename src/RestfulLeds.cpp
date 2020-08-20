#include "RestfulLeds.h"
#include <ArduinoJson.h>

RestfulLeds::RestfulLeds()
{
    _leds.emplace_back(1, 1, true);
    _leds.emplace_back(2, 5, false);
}

/**
 * @brief Handles GET request. Possible arguments:
 *        /leds - gets all leds
 *        /leds?id=xxx  -  gets led with given id
 *        /leds?gpio_pin=xxx - gets led with given gpio_pin
 * 
 * @param server 
 */
void RestfulLeds::HandleGet(ESP8266WebServer &server) const
{
    if (_leds.empty())
    {
        server.send(404);
        return;
    }

    if (server.args() > 0)
    {
        HandleGetArgs(server);
        return;
    }

    auto message = CreateJsonFromResource();
    server.send(200, "application/json", message);
}
/**
 * @brief Invokes when received GET request with arguments. Only one argument
 *        is accepted - id or gpio_pin.
 *         
 * @param server web server
 */
void RestfulLeds::HandleGetArgs(ESP8266WebServer &server) const
{
    String message;
    //only one argument
    if (server.args() != 1)
    {
        server.send(400);
        return;
    }
    if (server.argName(0) == "id")
    {
        int id = server.arg("id").toInt();
        auto it = std::find_if(_leds.begin(), _leds.end(), [id](const LedStatus &status) { return status.id == id; });
        if (it == _leds.end())
        {
            server.send(404);
            return;
        }
        message = CreateJsonFromResource(it);
    }
    else if (server.argName(0) == "gpio_pin")
    {
        int gpio_pin = server.arg("gpio_pin").toInt();
        auto it = std::find_if(_leds.begin(), _leds.end(), [gpio_pin](const LedStatus &status) { return status.gpio_pin == gpio_pin; });
        if (it == _leds.end())
        {
            server.send(404);
            return;
        }
        message = CreateJsonFromResource(it);
    }
    else
    {
        server.send(400);
        return;
    }

    server.send(200, "application/json", message);
}

/**
 * @brief Handle PUT request. If resource does not exists it will be created. Otherwise it will be modified.
 *        If user wants to modify resource he have to provide led id as the query argument
 * 
 * @param server web server
 */
void RestfulLeds::HandlePut(ESP8266WebServer &server)
{
    if (server.args() > 1)
    {
        ModifyResource(server);
        return;
    }
    if (_leds.size() >= MAX_LED_NUMBER)
    {
        Serial.println("Resource full.");
        server.send(507);
        return;
    }

    LedStatus parsed;
    if (!DeserializeAndCreateLedStatus(server, parsed))
    {
        return;
    }

    _leds.push_back(parsed);

    server.send(201);
}


/**
 * @brief Handle DELETE request. One nust provide ID argument in the query.
 * 
 * @param server web server
 */
void RestfulLeds::HandleDelete(ESP8266WebServer &server)
{

    if (server.args() != 1 || server.argName(0) != "id")
    {
        server.send(400);
        return;
    }

    int id = server.arg("id").toInt();
    auto it = std::find_if(_leds.begin(), _leds.end(), [id](const LedStatus &status) { return status.id == id; });

    //resource not found
    if (it == _leds.end())
    {
        server.send(404);
        return;
    }
    _leds.erase(it);
    server.send(204);
}
void RestfulLeds::HandlePost(ESP8266WebServer &server)
{
    server.send(501);
}

/**
 * @brief Creates Json from resource. If it == nullptr it gets whole resource. 
 *        Otherwise it creates json containing data from one led status resource.
 * 
 * @param it iterator pointing to given Led status
 * @return String json in string format, ready to be sent.
 */
String RestfulLeds::CreateJsonFromResource(const LedStatus *it) const
{
    String result;
    DynamicJsonDocument document(600);
    if (it == nullptr)
    {
        auto json_leds = document.createNestedArray("leds");

        for (const auto &led : _leds)
        {
            auto json_led = json_leds.createNestedObject();
            json_led["id"] = led.id;
            json_led["gpio_pin"] = led.gpio_pin;
            json_led["is_on"] = led.is_on;
        }
    }
    else
    {
        document["id"] = it->id;
        document["gpio_pin"] = it->gpio_pin;
        document["is_on"] = it->is_on;
    }
    serializeJsonPretty(document, result);
    return result;
}
/**
 * @brief Deserializes http request JSON argument and creates LedStatus.
 * 
 * @param server web server
 * @param out_led_status out variable, created LedStatus
 * @return true if deserielized without problems
 * @return false if not deserialized
 */
bool RestfulLeds::DeserializeAndCreateLedStatus(ESP8266WebServer &server, LedStatus &out_led_status) const
{
    DynamicJsonDocument document(600);
    auto content = server.arg("plain");

    auto parsing_error_code = deserializeJson(document, content);
    if (parsing_error_code)
    {
        Serial.print("Deserialization failed, error code: ");
        Serial.println(parsing_error_code.c_str());
        server.send(400);
        return false;
    }

    int id = document["id"];
    int gpio_pin = document["gpio_pin"];
    bool is_on = document["is_on"];

    //one of the following not specified in the request body
    if (id == 0 || gpio_pin == 0)
    {
        Serial.println("id or gpio_pin not specified");
        server.send(400);
        return false;
    }
    out_led_status = LedStatus(id, gpio_pin, is_on);
    return true;
}

/**
 * @brief Modifies resource of ID given as query argument. Other parameters are passed in JSON body/
 * 
 * @param server web server
 */
void RestfulLeds::ModifyResource(ESP8266WebServer &server)
{
    if (server.args() != 2 || server.argName(0) != "id")
    {
        Serial.println("Not valid argument");
        server.send(400);
        return;
    }

    int id = server.arg("id").toInt();
    auto it = std::find_if(_leds.begin(), _leds.end(), [id](const LedStatus &status) { return status.id == id; });

    //resource not found
    if (it == _leds.end())
    {
        server.send(404);
        return;
    }

    LedStatus parsed;
    if (!DeserializeAndCreateLedStatus(server, parsed))
    {
        return;
    }
    it->id = parsed.id;
    it->gpio_pin = parsed.gpio_pin;
    it->is_on = parsed.is_on;
    server.send(201);
}