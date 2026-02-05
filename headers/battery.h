#ifndef BATTERY_H
#define BATTERY_H

#include <string>

enum Status
{
    STATUS_CHARGING,
    STATUS_READY,
    STATUS_MAINTENANCE,
    STATUS_RENTED
};

struct Battery
{
    std::string type;
    float capacity_KWh;
    int soc; // 0 - 100
    int soh; // 0 - 100
    Status status;

    Battery(const std::string &type, float capacity_KWh, int soc, int soh, Status status)
        : type(type), capacity_KWh(capacity_KWh), soc(soc), soh(soh), status(status) {}

    Battery()
        : type(""), capacity_KWh(0.0), soc(0), soh(0), status(STATUS_READY) {}

    void info();
};

#endif