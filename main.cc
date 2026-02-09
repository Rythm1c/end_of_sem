#include <iostream>

#include "headers/database.h"
#include "headers/battery.h"
#include "headers/driver.h"
#include "headers/admin.h"
#include "headers/menus.h"

int main(void)
{
  Database db;

  std::cout << "loading admins database..." << std::endl;
  db.loadAdmins();
  std::cout << "loading drivers database..." << std::endl;
  db.loadDrivers();
  std::cout << "loading batteries database..." << std::endl;
  db.loadBatteries();

  while (true)
  {
    std::cout << std::endl;
    std::string mainMenuOption = mainMenu();

    // login selected
    if (mainMenuOption == "1")
    {
      std::cout << std::endl;
      std::cout << "login selected" << std::endl;
      std::string loginOption = loginMenu();
      if (loginOption == "1")
      {
        std::cout << std::endl;
        std::cout << "Admin login selected." << std::endl;
        auto *p_admin = adminLoginMenu(db);

        if (p_admin != nullptr)
        {
          std::cout << std::endl;
          while (p_admin != nullptr)
          {
            std::string adminMenuOption = adminMenu();
            if (adminMenuOption == "5")
            {
              p_admin = nullptr;
            }
            else if (adminMenuOption == "1")
            {
              listBatteriesMenu(db);
            }
            else if (adminMenuOption == "2")
            {
              listDriversMenu(db);
            }
            else if (adminMenuOption == "3")
            {
            }
            else if (adminMenuOption == "4")
            {
            }
          }
        }
      }
      else if (loginOption == "2")
      {
        std::cout << std::endl;
        std::cout << "Driver login selected." << std::endl;
      }
      else if (loginOption == "3")
      {
        continue;
      }
      else if (loginOption == "4")
      {
        break;
      }
    }

    // register selected
    else if (mainMenuOption == "2")
    {
      std::cout << std::endl;
      std::cout << "register a new admin selected" << std::endl;
      auto admin = adminRegisterMenu();
      db.addAdmin(new Administrator(admin));
    }

    else
    {
      break;
    }
  }

  db.saveAll();
  db.clear();

  return 0;
}
