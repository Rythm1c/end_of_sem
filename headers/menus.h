#ifndef MENUS_H
#define MENUS_H

#include "admin.h"
#include "driver.h"
#include <string>
#include <memory>

std::string mainMenu();
std::string loginMenu();

std::string adminMenu();
Administrator adminRegisterMenu();
Administrator *adminLoginMenu(const struct Database &db);
std::string manageBatteriesMenu();
std::unique_ptr<struct Battery> addBatteryMenu();
std::string batteryUpdateMenu();

std::string driverMenu();
Driver driverRegisterMenu();
Driver *driverLoginMenu(const struct Database &db);

struct Battery *selectBatteryForSwapMenu(const struct Database &db);
int getOldBatterySoCMenu();

// Helper functions
void pauseMenu();
int getValidBatteryId(const struct Database &db, const std::string &prompt);
int findBatteryId(const struct Database &db, struct Battery *battery);
void handleBatteryUpdate(struct Database &db);

#endif