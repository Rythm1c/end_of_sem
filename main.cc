#include <iostream>

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
      // admin login selected
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
            if (adminMenuOption == "4")
            {
              p_admin = nullptr;
            }
            // manage batteries selected
            else if (adminMenuOption == "3")
            {
              std::cout << std::endl;
              std::string batteryManagerOption = manageBatteriesMenu();
              if (batteryManagerOption == "8")
              {
                continue;
              }
              else if (batteryManagerOption == "1")
              {
                db.listBatteries('a');
                std::cout << std::endl;
                std::cout << "Press Enter to return to admin menu...";
                std::cin.ignore();
                std::cin.get();
              }
              else if (batteryManagerOption == "2")
              {
                db.listBatteries('b');
                std::cout << std::endl;
                std::cout << "Press Enter to return to admin menu...";
                std::cin.ignore();
                std::cin.get();
              }
              else if (batteryManagerOption == "3")
              {
                db.listBatteries('c');
                std::cout << std::endl;
                std::cout << "Press Enter to return to admin menu...";
                std::cin.ignore();
                std::cin.get();
              }
              else if (batteryManagerOption == "4")
              {
                db.listBatteries('d');
                std::cout << std::endl;
                std::cout << "Press Enter to return to admin menu...";
                std::cin.ignore();
                std::cin.get();
              }
              else if (batteryManagerOption == "5")
              {

                db.addBattery(addBatteryMenu());
                std::cout << ANSI_COLOR_GREEN << "Battery added success fully!" << ANSI_COLOR_DEFAULT << std::endl;
              }
              else if (batteryManagerOption == "6")
              {
                std::cout << std::endl;
                std::cout << "Update battery selected." << std::endl;
                int id;
                std::cout << "Enter battery id: ";
                std::cin >> id;
                while (!db.batteryExists(id))
                {
                  std::cout << ANSI_COLOR_RED << "Battery with ID " << id << " does not exist. Please enter a valid ID: " << ANSI_COLOR_DEFAULT;
                  std::cin >> id;
                }
                auto *battery = db.batteries[id];
                battery->info();
                std::cout << std::endl;

                while (battery != nullptr)
                {
                  std::string updateOption = batteryUpdateMenu();

                  if (updateOption == "6")
                  {
                    battery = nullptr;
                  }
                  else if (updateOption == "1")
                  {
                    std::cout << "Enter new battery type: ";
                    std::cin >> battery->type;
                    db.batteriesDirty = true;
                    std::cout << ANSI_COLOR_GREEN << "Battery type updated successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                  }
                  else if (updateOption == "2")
                  {
                    float newCapacity;
                    std::cout << "Enter new battery capacity (KWh): ";
                    std::cin >> newCapacity;
                    while (newCapacity <= 0)
                    {
                      std::cout << ANSI_COLOR_RED << "Invalid capacity. Please enter a positive number." << ANSI_COLOR_DEFAULT << std::endl;
                      std::cout << "Enter new battery capacity (KWh): ";
                      std::cin >> newCapacity;
                    }
                    battery->capacity_KWh = newCapacity;
                    db.batteriesDirty = true;
                    std::cout << ANSI_COLOR_GREEN << "Battery capacity updated successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                  }
                  else if (updateOption == "3")
                  {
                    int newSoc;
                    std::cout << "Enter new battery state of charge (SOC) (0-100): ";
                    std::cin >> newSoc;
                    while (newSoc < 0 || newSoc > 100)
                    {
                      std::cout << ANSI_COLOR_RED << "Invalid soc. Please enter a number between 0 and 100." << ANSI_COLOR_DEFAULT << std::endl;
                      std::cout << "Enter new battery state of charge (SOC) (0-100): ";
                      std::cin >> newSoc;
                    }
                    battery->soc = newSoc;
                    db.batteriesDirty = true;
                    std::cout << ANSI_COLOR_GREEN << "Battery SOC updated successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                  }
                  else if (updateOption == "4")
                  {
                    int newSoh;
                    std::cout << "Enter new battery state of health (SOH) (0-100): ";
                    std::cin >> newSoh;
                    while (newSoh < 0 || newSoh > 100)
                    {
                      std::cout << ANSI_COLOR_RED << "Invalid soh. Please enter a number between 0 and 100." << ANSI_COLOR_DEFAULT << std::endl;
                      std::cout << "Enter new battery state of health (SOH) (0-100): ";
                      std::cin >> newSoh;
                    }
                    battery->soh = newSoh;
                    db.batteriesDirty = true;
                    std::cout << ANSI_COLOR_GREEN << "Battery SOH updated successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                  }
                  else if (updateOption == "5")
                  {
                    int newStatus;
                    std::cout << "Enter new battery status (0: CHARGING, 1: READY, 2: MAINTENANCE, 3: RENTED): ";
                    std::cin >> newStatus;
                    while (newStatus != 0 ||
                           newStatus != 1 ||
                           newStatus != 2 ||
                           newStatus != 3)
                    {
                      std::cout << ANSI_COLOR_RED << "Invalid status. Please enter CHARGING, READY, MAINTENANCE, or RENTED." << ANSI_COLOR_DEFAULT << std::endl;
                      std::cout << "Enter new battery status (CHARGING, READY, MAINTENANCE, RENTED): ";
                      std::cin >> newStatus;
                    }
                    if (newStatus == 0)
                      battery->status = STATUS_CHARGING;
                    else if (newStatus == 1)
                      battery->status = STATUS_READY;
                    else if (newStatus == 2)
                      battery->status = STATUS_MAINTENANCE;
                    else if (newStatus == 3)
                      battery->status = STATUS_RENTED;
                    db.batteriesDirty = true;

                    std::cout << ANSI_COLOR_GREEN << "Battery status updated successfully!" << ANSI_COLOR_DEFAULT << std::endl;
                  }
                }
              }
              else if (batteryManagerOption == "7")
              {
                std::cout << std::endl;
                std::cout << "Remove battery selected." << std::endl;
                int id;
                std::cout << "Enter battery id: ";
                std::cin >> id;
                while (!db.batteryExists(id))
                {
                  std::cout << ANSI_COLOR_RED << "Battery with ID " << id << " does not exist. Please enter a valid ID: " << ANSI_COLOR_DEFAULT;
                  std::cin >> id;
                }
                db.removeBattery(id);
                std::cout << ANSI_COLOR_GREEN << "Battery removed successfully!" << ANSI_COLOR_DEFAULT << std::endl;
              }
            }
            else if (adminMenuOption == "1")
            {
              db.listDrivers();
            }
            else if (adminMenuOption == "2")
            {
              auto driver = driverRegisterMenu();
              db.addDriver(new Driver(driver));
            }
          }
        }
      }

      else if (loginOption == "2")
      {
        std::cout << std::endl;
        std::cout << "Driver login selected." << std::endl;
        auto *p_driver = driverLoginMenu(db);
        while (p_driver != nullptr)
        {
          std::string driverMenuOption = driverMenu();
          if (driverMenuOption == "4")
          {
            p_driver = nullptr;
          }
          else if (driverMenuOption == "1")
          {
            db.listBatteries('b');
            std::cout << std::endl;
            std::cout << "Press Enter to return to driver menu...";
            std::cin.ignore();
            std::cin.get();
          }
          else if (driverMenuOption == "2")
          {
            std::cout << std::endl;
            std::cout << "Battery Swap selected." << std::endl;

            // Get the old battery's SoC
            int oldSoC = getOldBatterySoCMenu();

            // Select a new fully charged battery
            auto selectedBattery = selectBatteryForSwapMenu(db);

            if (selectedBattery != nullptr)
            {
              // Find the battery ID for the selected battery
              int newBatteryId = -1;
              for (auto &pair : db.batteries)
              {
                if (pair.second == selectedBattery)
                {
                  newBatteryId = pair.first;
                  break;
                }
              }

              // Perform the swap - need to find old battery ID
              // For now, we'll ask the user for it
              std::cout << std::endl;
              std::cout << "Enter your current battery ID (to be returned): ";
              int oldBatteryId;
              std::cin >> oldBatteryId;

              if (db.swapBattery(p_driver, oldBatteryId, newBatteryId, oldSoC))
              {
                std::cout << ANSI_COLOR_GREEN << "Swap completed successfully!" << ANSI_COLOR_DEFAULT << std::endl;
              }
            }

            std::cout << std::endl;
            std::cout << "Press Enter to return to driver menu...";
            std::cin.ignore();
            std::cin.get();
          }
          else if (driverMenuOption == "3")
          {
            std::cout << std::endl;
            std::cout << "Your current energy credits: " << ANSI_COLOR_GREEN
                      << p_driver->credits << ANSI_COLOR_DEFAULT << std::endl;
            std::cout << std::endl;
            std::cout << "Press Enter to return to driver menu...";
            std::cin.ignore();
            std::cin.get();
          }
        }
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
