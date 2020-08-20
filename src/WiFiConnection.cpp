#include "WiFiConnection.h"

WiFiConnection::WiFiConnection(const String &ssid, const String &password, const String &hostname,
                               const IPAddress &ip, const IPAddress &gateway_ip,
                               const IPAddress &subnet, const IPAddress &dns) : _ssid(ssid),
                                                                                _password(password),
                                                                                _hostname(hostname),
                                                                                _ip(ip),
                                                                                _gateway_ip(gateway_ip),
                                                                                _subnet(subnet),
                                                                                _dns(dns)

{
}

/**
 * @brief Connects to the wifi using provided credentials (ssid and password)
 * 
 * @return int status code of the wifi connection
 */
int WiFiConnection::Connect()
{
    int retries = 0;

    WiFi.disconnect();
    WiFi.hostname(_hostname);
    WiFi.config(_ip, _gateway_ip, _subnet, _dns);
    WiFi.begin(_ssid, _password);
    WiFi.mode(WIFI_STA);

    while (WiFi.status() != WL_CONNECTED && retries < MAX_WIFI_INIT_RETRY)
    {
        ++retries;
        delay(WIFI_RETRY_DELAY);
    }
    Serial.println(WiFi.localIP());
    return WiFi.status();
}
