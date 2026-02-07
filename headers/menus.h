#ifndef MENUS_H
#define MENUS_H

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_PURPLE "\x1b[35m"
#define ANSI_COLOR_DEFAULT "\x1b[0m"

#include "admin.h"

int mainMenu();
int loginMenu();

Administrator adminRegisterMenu();
Administrator *adminLoginMenu(const struct Database &db);
int adminMenu();
void listBatteriesMenu(const struct Database &db);

#endif