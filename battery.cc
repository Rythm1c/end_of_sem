#include "headers/battery.h"
#include <iostream>

void Battery::info()
{

    std::string statusStr;
    switch (status)
    {
    case STATUS_CHARGING:
        statusStr = "CHARGING";
        break;
    case STATUS_READY:
        statusStr = "READY";
        break;
    case STATUS_MAINTENANCE:
        statusStr = "MAINTENANCE";
        break;
    case STATUS_RENTED:
        statusStr = "RENTED";
        break;
    default:
        statusStr = "UNKNOWN";
        break;
    }

    std::cout << "Battery Type: " << type << std::endl;
    std::cout << "Capacity (KWh): " << capacity_KWh << std::endl;
    std::cout << "State of Charge (SOC): " << soc << "%" << std::endl;
    std::cout << "State of Health (SOH): " << soh << "%" << std::endl;
    std::cout << "Status: " << statusStr << std::endl;
}