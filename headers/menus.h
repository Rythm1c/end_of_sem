#ifndef MENUS_H
#define MENUS_H

#include "admin.h"

int mainMenu();
int loginMenu();

Administrator adminRegisterMenu();
Administrator *adminLoginMenu(const struct Database &db);
int adminMenu();

#endif