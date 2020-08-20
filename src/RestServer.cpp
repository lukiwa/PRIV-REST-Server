#include "RestServer.h"

/**
 * @brief Begins espserver and binds Http methods to resource methods
 * 
 */
void RestServer::Begin(const String &endpoint, RestfulResource &resource)
{
    _esp_server.on("/", [this]() {
        _esp_server.send(200, "text/html", "This is my NodeMCU server.");
    });


    _esp_server.on(endpoint, HTTP_GET, std::bind(&RestfulResource::HandleGet, &resource, std::ref(_esp_server)));
    _esp_server.on(endpoint, HTTP_DELETE, std::bind(&RestfulResource::HandleDelete, &resource, std::ref(_esp_server)));
    _esp_server.on(endpoint, HTTP_POST, std::bind(&RestfulResource::HandlePost, &resource, std::ref(_esp_server)));
    _esp_server.on(endpoint, HTTP_PUT, std::bind(&RestfulResource::HandlePut, &resource, std::ref(_esp_server)));
    _esp_server.begin();
}

void RestServer::HandleClient()
{
    _esp_server.handleClient();
}