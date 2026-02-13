#include <iostream>
#include <memory>

#include "headers/database.h"
#include "headers/battery.h"
#include "headers/driver.h"
#include "headers/admin.h"
#include "headers/menus.h"
#include "colors.h"

int main(void)
{
  Database db;

  std::cout << "loading admins database..." << std::endl;
  db.loadAdmins();
  std::cout << "loading drivers database..." << std::endl;
  db.loadDrivers();
  std::cout << "loading batteries database..." << std::endl;
  db.loadBatteries();

  bool running = true;
  while (running)
  {
    std::cout << std::endl;
    std::string mainMenuOption = mainMenu();

    switch (mainMenuOption[0])
    {
      case '1': // login
      {
        std::cout << std::endl;
        std::cout << "login selected" << std::endl;
        std::string loginOption = loginMenu();
        
        switch (loginOption[0])
        {
          case '1': // admin login
          {
            std::cout << std::endl;
            std::cout << "Admin login selected." << std::endl;
            auto *p_admin = adminLoginMenu(db);

            if (p_admin != nullptr)
            {
              std::cout << std::endl;
              bool adminRunning = true;
              while (adminRunning)
              {
                std::string adminMenuOption = adminMenu();
                
                switch (adminMenuOption[0])
                {
                  case '1': // list drivers
                    db.listDrivers();
                    break;

                  case '2': // add driver
                  {
                    auto driver = driverRegisterMenu();
                    db.addDriver(std::make_unique<Driver>(driver));
                    break;
                  }

                  case '3': // manage batteries
                  {
                    std::string batteryManagerOption = manageBatteriesMenu();
                    
                    switch (batteryManagerOption[0])
                    {
                      case '1': case '2': case '3': case '4':
                      {
                        char filter = 'a';
                        switch (batteryManagerOption[0])
                        {
                          case '1': filter = 'a'; break;
                          case '2': filter = 'b'; break;
                          case '3': filter = 'c'; break;
                          case '4': filter = 'd'; break;
                        }
                        db.listBatteries(filter);
                        pauseMenu();
                        break;
                      }

                      case '5':
                      {
                        db.addBattery(addBatteryMenu());
                        std::cout << ANSI_COLOR_GREEN << "Battery added successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                        break;
                      }

                      case '6':
                      {
                        handleBatteryUpdate(db);
                        break;
                      }

                      case '7':
                      {
                        std::cout << std::endl;
                        std::cout << "Remove battery selected." << std::endl;
                        int id = getValidBatteryId(db, "Enter battery id: ");
                        db.removeBattery(id);
                        std::cout << ANSI_COLOR_GREEN << "Battery removed successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                        break;
                      }

                      case '8':
                        break; // Return to admin menu

                      default:
                        std::cout << ANSI_COLOR_RED << "Invalid option." << ANSI_COLOR_DEFAULT << std::endl;
                    }
                    break;
                  }

                  case '4': // logout
                    adminRunning = false;
                    break;
                    
                  default:
                    std::cout << ANSI_COLOR_RED << "Invalid option." << ANSI_COLOR_DEFAULT << std::endl;
                }
              }
            }
            break;
          }

          case '2': // driver login
          {
            std::cout << std::endl;
            std::cout << "Driver login selected." << std::endl;
            auto *p_driver = driverLoginMenu(db);
            
            if (p_driver != nullptr)
            {
              bool driverRunning = true;
              while (driverRunning)
              {
                std::string driverMenuOption = driverMenu();
                
                switch (driverMenuOption[0])
                {
                  case '1': // list available batteries
                    db.listBatteries('b');
                    pauseMenu();
                    break;

                  case '2': // battery swap
                  {
                    std::cout << std::endl;
                    std::cout << "Battery Swap selected." << std::endl;
                    int oldSoC = getOldBatterySoCMenu();
                    auto selectedBattery = selectBatteryForSwapMenu(db);

                    if (selectedBattery != nullptr)
                    {
                      int newBatteryId = findBatteryId(db, selectedBattery);
                      std::cout << std::endl;
                      std::cout << "Enter your current battery ID (to be returned): ";
                      int oldBatteryId;
                      std::cin >> oldBatteryId;

                      if (db.swapBattery(p_driver, oldBatteryId, newBatteryId, oldSoC))
                      {
                        std::cout << ANSI_COLOR_GREEN << "Swap completed successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                      }
                    }
                    pauseMenu();
                    break;
                  }

                  case '3': // view credits
                    std::cout << std::endl;
                    std::cout << "Your current energy credits: " << ANSI_COLOR_GREEN
                              << p_driver->credits << ANSI_COLOR_DEFAULT << std::endl;
                    pauseMenu();
                    break;

                  case '4': // logout
                    driverRunning = false;
                    break;
                    
                  default:
                    std::cout << ANSI_COLOR_RED << "Invalid option." << ANSI_COLOR_DEFAULT << std::endl;
                }
              }
            }
            break;
          }

          case '3': // back
            break;

          case '4': // exit
            running = false;
            break;

          default:
            std::cout << ANSI_COLOR_RED << "Invalid option." << ANSI_COLOR_DEFAULT << std::endl;
        }
        break;
      }

      case '2': // register
      {
        std::cout << std::endl;
        std::cout << "register a new admin selected" << std::endl;
        auto admin = adminRegisterMenu();
        db.addAdmin(std::make_unique<Administrator>(admin));
        break;
      }

      case '3': // exit
        running = false;
        break;

      default:
        std::cout << ANSI_COLOR_RED << "Invalid option." << ANSI_COLOR_DEFAULT << std::endl;
    }
  }

  db.saveAll();
  db.clear();

  return 0;
}
