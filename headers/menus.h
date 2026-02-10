#ifndef MENUS_H
#define MENUS_H

#include "admin.h"
#include "driver.h"
#include <string>

std::string mainMenu();
std::string loginMenu();

std::string adminMenu();
Administrator adminRegisterMenu();
Administrator *adminLoginMenu(const struct Database &db);
std::string manageBatteriesMenu();
struct Battery *addBatteryMenu();
std::string batteryUpdateMenu();

std::string driverMenu();
Driver driverRegisterMenu();
Driver *driverLoginMenu(const struct Database &db);

struct Battery *selectBatteryForSwapMenu(const struct Database &db);
int getOldBatterySoCMenu();

#endif