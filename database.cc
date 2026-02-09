#include "headers/database.h"
#include "headers/admin.h"
#include "headers/battery.h"
#include "headers/driver.h"

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