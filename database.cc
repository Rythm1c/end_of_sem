#include "headers/database.h"
#include "headers/admin.h"
#include "headers/battery.h"
#include "headers/driver.h"
#include "headers/constants.h"
#include "colors.h"
#include <iomanip>

#include <fstream>
#include <sstream>
#include <iostream>

void Database::loadAdmins()
{
    std::ifstream file(ADMIN_DB_PATH);
    if (!file.is_open())
    {
        std::cerr << "Failed to open admin database file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int id;
        std::string name, password;
        if (!(iss >> id >> name >> password))
        {
            continue; // Skip malformed lines
        }
        Administrator *admin = new Administrator(name, password);
        admins[id] = admin;
    }

    file.close();
    // Update nextAdminId to be one past the highest ID loaded
    if (!admins.empty())
    {
        nextAdminId = admins.rbegin()->first + 1;
    }
}

void Database::addAdmin(Administrator *admin)
{
    int newId = nextAdminId++;
    admins.insert(std::make_pair(newId, admin));
    adminsDirty = true;
}

void Database::removeAdmin(int id)
{
    auto it = admins.find(id);
    if (it != admins.end())
    {
        delete it->second;
        admins.erase(it);
        adminsDirty = true;
    }
}

void Database::loadBatteries()
{
    std::ifstream file(BATTERY_DB_PATH);
    if (!file.is_open())
    {
        std::cerr << "Failed to open battery database file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int id;
        std::string type;
        float capacity_KWh;
        int soc, soh;

        std::string status;
        if (!(iss >> id >> type >> capacity_KWh >> soc >> soh >> status))
        {
            continue; // Skip malformed lines
        }

        Status batteryStatus;
        if (status == "CHARGING")
            batteryStatus = STATUS_CHARGING;
        else if (status == "READY")
            batteryStatus = STATUS_READY;
        else if (status == "MAINTENANCE")
            batteryStatus = STATUS_MAINTENANCE;
        else if (status == "RENTED")
            batteryStatus = STATUS_RENTED;
        else
            batteryStatus = STATUS_READY; // Default status

        Battery *battery = new Battery(type, capacity_KWh, soc, soh, batteryStatus);
        batteries[id] = battery;
    }

    file.close();
    // Update nextBatteryId to be one past the highest ID loaded
    if (!batteries.empty())
    {
        nextBatteryId = batteries.rbegin()->first + 1;
    }
}
bool Database::batteryExists(int id)
{
    return batteries.find(id) != batteries.end();
}

void Database::addBattery(struct Battery *battery)
{
    int newId = nextBatteryId++;
    batteries[newId] = battery;
    batteriesDirty = true;
}
void Database::removeBattery(int id)
{
    auto it = batteries.find(id);
    if (it != batteries.end())
    {
        delete it->second;
        batteries.erase(it);
        batteriesDirty = true;
    }
}

void Database::loadDrivers()
{
    std::ifstream file(USER_DB_PATH);
    if (!file.is_open())
    {
        std::cerr << "Failed to open driver database file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int id;
        std::string name, password, plate;
        float credits;
        if (!(iss >> id >> name >> password >> plate >> credits))
        {
            continue; // Skip malformed lines
        }
        Driver *driver = new Driver(name, password, plate, credits);
        drivers[id] = driver;
    }

    file.close();
    // Update nextDriverId to be one past the highest ID loaded
    if (!drivers.empty())
    {
        nextDriverId = drivers.rbegin()->first + 1;
    }
}
bool Database::driverExists(int id)
{
    return drivers.find(id) != drivers.end();
}

void Database::addDriver(struct Driver *driver)
{
    int newId = nextDriverId++;
    drivers[newId] = driver;
    driversDirty = true;
}

void Database::removeDriver(int id)
{
    auto it = drivers.find(id);
    if (it != drivers.end())
    {
        delete it->second;
        drivers.erase(it);
        driversDirty = true;
    }
}

bool Database::swapBattery(struct Driver *driver, int oldBatteryId, int newBatteryId, int oldSoC)
{
    // Check if both batteries exist
    if (batteries.find(oldBatteryId) == batteries.end() ||
        batteries.find(newBatteryId) == batteries.end())
    {
        std::cout << ANSI_COLOR_RED << "One or both battery IDs do not exist." << ANSI_COLOR_DEFAULT << std::endl;
        return false;
    }

    Battery *oldBattery = batteries[oldBatteryId];
    Battery *newBattery = batteries[newBatteryId];

    // Check if new battery is ready and fully charged
    if (newBattery->status != STATUS_READY || newBattery->soc != 100)
    {
        std::cout << ANSI_COLOR_RED << "New battery must be Ready and fully charged (100% SoC)." << ANSI_COLOR_DEFAULT << std::endl;
        return false;
    }

    // Validate old SoC
    if (oldSoC < 0 || oldSoC > 100)
    {
        std::cout << ANSI_COLOR_RED << "Invalid old SoC value. Must be between 0 and 100." << ANSI_COLOR_DEFAULT << std::endl;
        return false;
    }

    // Calculate energy difference and cost
    int energyDifference = 100 - oldSoC; // New is always 100%
    float cost = energyDifference * RATE_PER_PERCENT;

    // Check if driver has enough credits
    if (driver->credits < cost)
    {
        std::cout << ANSI_COLOR_RED << "Insufficient energy credits. Required: " << cost
                  << ", Available: " << driver->credits << ANSI_COLOR_DEFAULT << std::endl;
        return false;
    }

    // Perform the swap
    driver->credits -= cost;              // Deduct cost from driver's credits
    newBattery->status = STATUS_RENTED;   // Mark new battery as rented
    oldBattery->status = STATUS_CHARGING; // Old battery becomes charging
    oldBattery->soc = oldSoC;             // Update old battery's current SoC

    // Mark as dirty for save
    driversDirty = true;
    batteriesDirty = true;

    std::cout << ANSI_COLOR_GREEN << "Battery swap successful!" << ANSI_COLOR_DEFAULT << std::endl;
    std::cout << "Energy difference: " << energyDifference << "%" << std::endl;
    std::cout << "Cost: " << cost << " credits" << std::endl;
    std::cout << "Remaining credits: " << driver->credits << std::endl;

    return true;
}

bool Database::adminExists(int id)
{
    return admins.find(id) != admins.end();
}

void Database::saveAdmins()
{
    std::ofstream file(ADMIN_DB_PATH);
    if (!file.is_open())
    {
        std::cerr << "Failed to open admin database file for writing." << std::endl;
        return;
    }

    for (const auto &pair : admins)
    {
        int id = pair.first;
        Administrator *admin = pair.second;
        file << id << " " << admin->name << " " << admin->password << std::endl;
    }

    file.close();
}

void Database::saveBatteries()
{
    std::ofstream file(BATTERY_DB_PATH);
    if (!file.is_open())
    {
        std::cerr << "Failed to open battery database file for writing." << std::endl;
        return;
    }

    for (const auto &pair : this->batteries)
    {
        int id = pair.first;
        Battery *battery = pair.second;
        std::string statusStr;
        switch (battery->status)
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
            statusStr = "READY";
            break;
        }
        file << id << " " << battery->type << " " << battery->capacity_KWh << " "
             << battery->soc << " " << battery->soh << " " << statusStr << std::endl;
    }

    file.close();
}

void Database::saveDrivers()
{
    std::ofstream file(USER_DB_PATH);
    if (!file.is_open())
    {
        std::cerr << "Failed to open driver database file for writing." << std::endl;
        return;
    }

    for (const auto &pair : drivers)
    {
        int id = pair.first;
        Driver *driver = pair.second;
        file << id << " " << driver->name << " " << driver->password << " "
             << driver->plate << " " << driver->credits << std::endl;
    }

    file.close();
}

void Database::saveAll()
{
    if (this->adminsDirty)
    {
        this->saveAdmins();
        this->adminsDirty = false;
    }
    if (this->driversDirty)
    {
        this->saveDrivers();
        this->driversDirty = false;
    }
    if (this->batteriesDirty)
    {
        this->saveBatteries();
        this->batteriesDirty = false;
    }
}
/// "a" lists all drivers
/// "b" lists all available batteries
/// "c" lists all charging batteries
/// "d" lists all batteries under maintainance
void Database::listBatteries(char filter)
{
    if (this->batteries.empty())
    {
        std::cout << ANSI_COLOR_PURPLE << "No batteries available." << ANSI_COLOR_DEFAULT << std::endl;
    }
    else
    {
        switch (filter)
        {
        case 'a':
            std::cout << ANSI_COLOR_YELLOW << std::left
                      << std::setw(6) << "ID"
                      << std::setw(15) << "Type"
                      << std::setw(15) << "Capacity(kWh)"
                      << std::setw(8) << "SOC(%)"
                      << std::setw(8) << "SOH(%)"
                      << std::setw(15) << "Status"
                      << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::string(67, '-') << ANSI_COLOR_DEFAULT << std::endl;

            for (auto &pair : this->batteries)
            {
                int id = pair.first;
                Battery *battery = pair.second;

                std::string status_str;
                switch (battery->status)
                {
                case STATUS_CHARGING:
                    status_str = "Charging";
                    break;
                case STATUS_READY:
                    status_str = "Ready";
                    break;
                case STATUS_MAINTENANCE:
                    status_str = "Maintenance";
                    break;
                case STATUS_RENTED:
                    status_str = "Rented";
                    break;
                default:
                    status_str = "Unknown";
                }

                std::cout << ANSI_COLOR_PURPLE << std::left
                          << std::setw(6) << id
                          << std::setw(15) << battery->type
                          << std::setw(15) << battery->capacity_KWh
                          << std::setw(8) << battery->soc
                          << std::setw(8) << battery->soh
                          << std::setw(15) << status_str
                          << ANSI_COLOR_DEFAULT << std::endl;
            }

            break;
        case 'c':
            std::cout << ANSI_COLOR_YELLOW << "=== List of charging batteries ===" << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::left
                      << std::setw(6) << "ID"
                      << std::setw(15) << "Type"
                      << std::setw(15) << "Capacity(kWh)"
                      << std::setw(8) << "SOC(%)"
                      << std::setw(8) << "SOH(%)"
                      << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::string(52, '-') << ANSI_COLOR_DEFAULT << std::endl;
            for (auto &pair : this->batteries)
            {
                int id = pair.first;
                Battery *battery = pair.second;

                if (battery->status == STATUS_CHARGING)
                {
                    std::cout << ANSI_COLOR_PURPLE << std::left
                              << std::setw(6) << id
                              << std::setw(15) << battery->type
                              << std::setw(15) << battery->capacity_KWh
                              << std::setw(8) << battery->soc
                              << std::setw(8) << battery->soh
                              << ANSI_COLOR_DEFAULT << std::endl;
                }
            }
            break;

        case 'b':
            std::cout << ANSI_COLOR_YELLOW << "=== List of available batteries ===" << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::left
                      << std::setw(6) << "ID"
                      << std::setw(15) << "Type"
                      << std::setw(15) << "Capacity(kWh)"
                      << std::setw(8) << "SOC(%)"
                      << std::setw(8) << "SOH(%)"
                      << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::string(52, '-') << ANSI_COLOR_DEFAULT << std::endl;
            for (auto &pair : this->batteries)
            {
                int id = pair.first;
                Battery *battery = pair.second;

                if (battery->status == STATUS_CHARGING)
                {
                    std::cout << ANSI_COLOR_PURPLE << std::left
                              << std::setw(6) << id
                              << std::setw(15) << battery->type
                              << std::setw(15) << battery->capacity_KWh
                              << std::setw(8) << battery->soc
                              << std::setw(8) << battery->soh
                              << ANSI_COLOR_DEFAULT << std::endl;
                }
            }
            break;
        case 'd':
            std::cout << ANSI_COLOR_YELLOW << "=== List of batteries under maintainance ===" << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::left
                      << std::setw(6) << "ID"
                      << std::setw(15) << "Type"
                      << std::setw(15) << "Capacity(kWh)"
                      << std::setw(8) << "SOC(%)"
                      << std::setw(8) << "SOH(%)"
                      << ANSI_COLOR_DEFAULT << std::endl;

            std::cout << ANSI_COLOR_YELLOW << std::string(52, '-') << ANSI_COLOR_DEFAULT << std::endl;
            for (auto &pair : this->batteries)
            {
                int id = pair.first;
                Battery *battery = pair.second;

                if (battery->status == STATUS_CHARGING)
                {
                    std::cout << ANSI_COLOR_PURPLE << std::left
                              << std::setw(6) << id
                              << std::setw(15) << battery->type
                              << std::setw(15) << battery->capacity_KWh
                              << std::setw(8) << battery->soc
                              << std::setw(8) << battery->soh
                              << ANSI_COLOR_DEFAULT << std::endl;
                }
            }
            break;
        }
    }
}

void Database::listDrivers()
{
    std::cout << ANSI_COLOR_YELLOW << std::left
              << std::setw(6) << "ID"
              << std::setw(20) << "Name"
              << std::setw(20) << "License Plate"
              << std::setw(12) << "Credits"
              << ANSI_COLOR_DEFAULT << std::endl;

    std::cout << ANSI_COLOR_YELLOW << std::string(58, '-') << ANSI_COLOR_DEFAULT << std::endl;

    if (this->drivers.empty())
    {
        std::cout << ANSI_COLOR_PURPLE << "No drivers available." << ANSI_COLOR_DEFAULT << std::endl;
    }
    else
    {
        for (auto &pair : this->drivers)
        {
            int id = pair.first;
            Driver *driver = pair.second;

            std::cout << ANSI_COLOR_PURPLE << std::left
                      << std::setw(6) << id
                      << std::setw(20) << driver->name
                      << std::setw(20) << driver->plate
                      << std::setw(12) << std::fixed << std::setprecision(2) << driver->credits
                      << ANSI_COLOR_DEFAULT << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Press Enter to return to admin menu...";
    std::cin.ignore();
    std::cin.get();
}

void Database::clear()
{
    for (auto &pair : this->admins)
    {
        delete pair.second;
    }
    this->admins.clear();

    for (auto &pair : this->drivers)
    {
        delete pair.second;
    }
    this->drivers.clear();

    for (auto &pair : this->batteries)
    {
        delete pair.second;
    }
    this->batteries.clear();
}