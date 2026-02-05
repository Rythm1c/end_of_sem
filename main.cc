#include <iostream>

#include "headers/database.h"
#include "headers/battery.h"
#include "headers/driver.h"
#include "headers/admin.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_DEFAULT "\x1b[0m"

int mainMenu();
int loginMenu();

Administrator adminRegisterMenu();
int adminMenu();

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
    int mainMenuOption = mainMenu();

    // login selected
    if (mainMenuOption == 1)
    {
      std::cout << std::endl;
      std::cout << "login selected" << std::endl;
      int loginOption = loginMenu();
      if (loginOption == 1)
      {
        std::cout << std::endl;
        std::cout << "Admin login selected." << std::endl;
        int *admin_id = nullptr;
      }
      else if (loginOption == 2)
      {
        std::cout << std::endl;
        std::cout << "Driver login selected." << std::endl;
      }
      else if (loginOption == 3)
      {
        continue;
      }
      else if (loginOption == 4)
      {
        break;
      }
    }

    // register selected
    else if (mainMenuOption == 2)
    {
      std::cout << std::endl;
      std::cout << "register a new admin selected" << std::endl;
      Administrator admin = adminRegisterMenu();
      db.addAdmin(new Administrator(admin));
    }

    else
    {
      break;
    }
  }
  /*
  db.addAdmin(new Administrator("admin1", "adminpass1"));
  db.addDriver(new Driver("driver1", "driverpass1", "ABC123", 100.0));
  db.addBattery(new Battery("Li-Ion", 75.0, 80, 90, STATUS_READY)); */
  
  db.saveAll();
  db.clear();

  return 0;
}

int mainMenu()
{
  std::cout << ANSI_COLOR_YELLOW << "=== Main Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
  std::cout << "1. login" << std::endl;
  std::cout << "2. register" << std::endl;
  std::cout << ANSI_COLOR_RED << "3. Exit" << ANSI_COLOR_DEFAULT << std::endl;

  int choice;

  while (true)
  {
    std::cin >> choice;
    if (choice == 1 || choice == 2 || choice == 3)
    {
      break;
    }
    else
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }

  return choice;
}

int loginMenu()
{
  int choice;

  std::cout << ANSI_COLOR_YELLOW << "=== Login Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
  std::cout << "1. Admin Login" << std::endl;
  std::cout << "2. Driver Login" << std::endl;
  std::cout << "3. back" << std::endl;
  std::cout << ANSI_COLOR_RED << "4. Exit" << ANSI_COLOR_DEFAULT << std::endl;

  while (true)
  {

    std::cin >> choice;

    if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
    {
      break;
    }
    else
    {
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }

  return choice;
}

Administrator adminRegisterMenu()
{
  std::cout << ANSI_COLOR_YELLOW << "=== Admin Register Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
  std::string name, password, confirmation;

  std::cout << "Enter your name: ";
  std::cin >> name;

  std::cout << "Enter your password: ";
  std::cin >> password;

  while (true)
  {
    std::cout << "confirm your password: ";
    std::cin >> confirmation;

    if (confirmation == password)
      break;
    else
      std::cout << "passwords do not match!" << std::endl;
  }

  return Administrator(name, password);
}

int adminMenu()
{

  std::cout << "1. list available batteries" << std::endl;
  std::cout << "2. list EV drivers" << std::endl;
  std::cout << "3. create driver account" << std::endl;
  std::cout << "4. manage batteries" << std::endl;
  std::cout << "5. logout" << std::endl;

  int choice;

  while (true)
  {
    std::cin >> choice;
    if (choice == 1 || choice == 2 || choice == 3)
      break;
    else
      std::cout << "invalid option try again." << std::endl;
  }

  return choice;
}