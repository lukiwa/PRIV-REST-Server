#pragma once

struct LedStatus
{
    LedStatus(int id, int gpio_pin, bool is_on) : id(id), gpio_pin(gpio_pin), is_on(is_on) {}
    LedStatus() = default;
    int id;
    int gpio_pin;
    bool is_on;
};
