#ifndef DATABASE_H
#define DATABASE_H

#define ADMIN_DB_PATH "data/admins.txt"
#define USER_DB_PATH "data/drivers.txt"
#define BATTERY_DB_PATH "data/batteries.txt"

#include <string>
#include <map>

struct Database
{
    int nextAdminId;
    int nextDriverId;
    int nextBatteryId;

    bool adminsDirty;
    bool driversDirty;
    bool batteriesDirty;

    std::map<int, struct Administrator *> admins;
    std::map<int, struct Driver *> drivers;
    std::map<int, struct Battery *> batteries;

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

    void addAdmin(struct Administrator *);
    void addDriver(struct Driver *);
    void addBattery(struct Battery *);

    void removeAdmin(int);
    void removeDriver(int);
    void removeBattery(int);

    // Helper methods for checking existence
    bool adminExists(int);
    bool driverExists(int);
    bool batteryExists(int);

    void clear();
};

#endif