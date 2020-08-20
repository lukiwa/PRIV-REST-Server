#include "WiFiConnectionBuilder.h"
typedef WiFiConnectionBuilder Builder;

Builder &Builder::Ssid(const String &ssid)
{
    _ssid = ssid;
    return *this;
}
Builder &Builder::Password(const String &password)
{
    _password = password;
    return *this;
}
Builder &Builder::Hostname(const String &hostname)
{
    _hostname = hostname;
    return *this;
}

Builder &Builder::SelectedIP(const IPAddress &ip)
{
    _ip = ip;
    return *this;
}
Builder &Builder::GatewayIP(const IPAddress &gateway_ip)
{
    _gateway_ip = gateway_ip;
    return *this;
}
Builder &Builder::Subnet(const IPAddress &subnet)
{
    _subnet = subnet;
    return *this;
}
Builder &Builder::Dns(const IPAddress &dns)
{
    _dns = dns;
    return *this;
}
WiFiConnection Builder::Build()
{
    return WiFiConnection(_ssid, _password, _hostname, _ip, _gateway_ip, _subnet, _dns);
}