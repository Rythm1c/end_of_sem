#ifndef DATABASE_H
#define DATABASE_H

#define ADMIN_DB_PATH "data/admins.txt"
#define USER_DB_PATH "data/drivers.txt"
#define BATTERY_DB_PATH "data/batteries.txt"

#include <string>
#include <map>
#include <memory>
#include "admin.h"
#include "driver.h"
#include "battery.h"

struct Database
{
    int nextAdminId;
    int nextDriverId;
    int nextBatteryId;

    bool adminsDirty;
    bool driversDirty;
    bool batteriesDirty;

    std::map<int, std::unique_ptr<Administrator>> admins;
    std::map<int, std::unique_ptr<Driver>> drivers;
    std::map<int, std::unique_ptr<Battery>> batteries;

    Database()
        : nextAdminId(1),
          nextDriverId(1),
          nextBatteryId(1),
          adminsDirty(false),
          driversDirty(false),
          batteriesDirty(false) {}

    ~Database() {}

    void loadAdmins();
    void loadDrivers();
    void loadBatteries();

    void saveAdmins();
    void saveDrivers();
    void saveBatteries();
    void saveAll();

    void addAdmin(std::unique_ptr<Administrator>);
    void addDriver(std::unique_ptr<Driver>);
    void addBattery(std::unique_ptr<Battery>);

    void removeAdmin(int);
    void removeDriver(int);
    void removeBattery(int);

    // Helper methods for checking existence
    bool adminExists(int) const;
    bool driverExists(int) const;
    bool batteryExists(int) const;
    
    /// "a" lists all drivers
    /// "b" lists all available batteries
    /// "c" lists all charging batteries
    /// "d" lists all batteries under maintainance
    void listBatteries(char);
    void listDrivers();

    // Battery swap operation
    bool swapBattery(struct Driver *driver, int oldBatteryId, int newBatteryId, int oldSoC);

    void clear();
};

#endif