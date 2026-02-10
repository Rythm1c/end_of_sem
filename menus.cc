#include "headers/menus.h"
#include "headers/database.h"
#include "headers/battery.h"
#include "colors.h"

#include <iostream>
#include <iomanip>

std::string mainMenu()
{
    std::cout << ANSI_COLOR_YELLOW << "=== Main Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::cout << "1. login" << std::endl;
    std::cout << "2. register" << std::endl;
    std::cout << ANSI_COLOR_RED << "3. Exit" << ANSI_COLOR_DEFAULT << std::endl;

    std::string choice;

    while (true)
    {
        std::cin >> choice;
        if (choice == "1" ||
            choice == "2" ||
            choice == "3")
        {
            break;
        }
        else
        {
            std::cout << ANSI_COLOR_RED << "Invalid choice. Please try again!" << ANSI_COLOR_DEFAULT << std::endl;
        }
    }

    return choice;
}

std::string loginMenu()
{
    std::string choice;

    std::cout << ANSI_COLOR_YELLOW << "=== Login Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::cout << "1. Admin Login" << std::endl;
    std::cout << "2. Driver Login" << std::endl;
    std::cout << "3. back" << std::endl;
    std::cout << ANSI_COLOR_RED << "4. Exit" << ANSI_COLOR_DEFAULT << std::endl;

    while (true)
    {

        std::cin >> choice;

        if (choice == "1" ||
            choice == "2" ||
            choice == "3" ||
            choice == "4")
        {
            break;
        }
        else
        {
            std::cout << ANSI_COLOR_RED << "Invalid choice. Please try again." << ANSI_COLOR_DEFAULT << std::endl;
        }
    }

    return choice;
}

Administrator adminRegisterMenu()
{
    std::cout << ANSI_COLOR_YELLOW << "=== Admin Register Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::string name, password, confirmation;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your password: ";
    std::cin >> password;

    while (true)
    {
        std::cout << "confirm your password: ";
        std::cin >> confirmation;

        if (confirmation == password)
            break;
        else
            std::cout << ANSI_COLOR_RED << "passwords do not match!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return Administrator(name, password);
}

Administrator *adminLoginMenu(const Database &db)
{
    std::cout << ANSI_COLOR_YELLOW << "=== Admin login Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::string name, password;

    Administrator *p_admin;

    while (true)
    {
        std::cout << "Enter your name: ";
        std::cin >> name;

        std::cout << "Enter your password: ";
        std::cin >> password;

        bool found = false;
        for (auto &pair : db.admins)
        {
            auto admin = pair.second;
            if (admin->name == name)
            {
                if (admin->password == password)
                {
                    // once a match is found exit loop and return the admin user pointer
                    p_admin = pair.second;
                    found = true;
                    break;
                }
            }
        }

        if (found)
        {
            std::cout << ANSI_COLOR_GREEN << "Welcome back " << name << ANSI_COLOR_DEFAULT << std::endl;
            break;
        }

        std::cout << ANSI_COLOR_RED << "invalid login details!\n"
                  << "username or password wrong!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return p_admin;
}

std::string adminMenu()
{

    std::cout << "1. list EV drivers" << std::endl;
    std::cout << "2. create driver account" << std::endl;
    std::cout << "3. manage batteries" << std::endl;
    std::cout << ANSI_COLOR_RED << "4. logout" << ANSI_COLOR_DEFAULT << std::endl;

    std::string choice;

    while (true)
    {
        std::cin >> choice;
        if (choice == "1" ||
            choice == "2" ||
            choice == "3" ||
            choice == "4")
            break;
        else
            std::cout << ANSI_COLOR_RED << "invalid option. try again!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return choice;
}

Driver driverRegisterMenu()
{
    std::cout << ANSI_COLOR_YELLOW << "=== Ev Driver Register Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::string name, password, license, confirmation;

    std::cout << "Enter driver's name: ";
    std::cin >> name;

    std::cout << "Enter driver's license: ";
    std::cin >> license;

    std::cout << "Enter driver's password: ";
    std::cin >> password;
    while (true)
    {
        std::cout << "confirm driver's password: ";
        std::cin >> confirmation;

        if (confirmation == password)
            break;
        else
            std::cout << ANSI_COLOR_RED << "passwords do not match!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return Driver(name, password, license, 500);
}

Driver *driverLoginMenu(const struct Database &db)
{
    std::cout << ANSI_COLOR_YELLOW << "=== Driver login Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::string name, password;

    Driver *p_driver;

    while (p_driver != nullptr)
    {
        std::cout << "Enter your name: ";
        std::cin >> name;

        std::cout << "Enter your password: ";
        std::cin >> password;

        bool found = false;
        for (auto &pair : db.drivers)
        {
            auto admin = pair.second;
            if (admin->name == name)
            {
                if (admin->password == password)
                {
                    // once a match is found exit loop and return the admin user pointer
                    p_driver = pair.second;
                    found = true;
                    break;
                }
            }
        }

        if (found)
        {
            std::cout << ANSI_COLOR_GREEN << "Welcome back " << name << ANSI_COLOR_DEFAULT << std::endl;
            break;
        }

        std::cout << ANSI_COLOR_RED << "invalid login details!\n"
                  << "username or password wrong!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return p_driver;
}

std::string driverMenu()
{

    std::cout << "1. list available batteries" << std::endl;
    std::cout << "2. swap batteries" << std::endl;
    std::cout << "3. view energy credits" << std::endl;
    std::cout << ANSI_COLOR_RED << "4. logout" << ANSI_COLOR_DEFAULT << std::endl;

    std::string choice;

    while (true)
    {
        std::cin >> choice;
        if (choice == "1" ||
            choice == "2" ||
            choice == "3" ||
            choice == "4")
            break;
        else
            std::cout << ANSI_COLOR_RED << "invalid option. try again!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return choice;
}

std::string manageBatteriesMenu()
{
    std::cout << "1. list all batteries" << std::endl;
    std::cout << "2. list available batteries" << std::endl;
    std::cout << "3. list charging batteries" << std::endl;
    std::cout << "4. list batteries under maintainance" << std::endl;
    std::cout << "5. add battery" << std::endl;
    std::cout << "6. update battery" << std::endl;
    std::cout << "7. remove battery" << std::endl;
    std::cout << ANSI_COLOR_RED << "8. back" << ANSI_COLOR_DEFAULT << std::endl;

    std::string choice;

    while (true)
    {
        std::cin >> choice;
        if (choice == "1" ||
            choice == "2" ||
            choice == "3" ||
            choice == "4" ||
            choice == "5" ||
            choice == "6" ||
            choice == "7" ||
            choice == "8")
            break;
        else
            std::cout << ANSI_COLOR_RED << "invalid option. try again!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return choice;
}

Battery *addBatteryMenu()
{
    std::string type;
    float capacity_KWh;
    int soc; // 0 - 100
    int soh; // 0 - 100
    Status status;

    std::cout << "Enter battery type: ";
    std::cin >> type;

    std::cout << "Enter battery capacity (KWh): ";
    std::cin >> capacity_KWh;
    while (capacity_KWh <= 0)
    {
        std::cout << ANSI_COLOR_RED << "Invalid capacity. Please enter a positive number." << ANSI_COLOR_DEFAULT << std::endl;
        std::cout << "Enter battery capacity (KWh): ";
        std::cin >> capacity_KWh;
    }

    std::cout << "Enter battery state of charge (SOC) (0-100): ";
    std::cin >> soc;
    while (soc < 0 || soc > 100)
    {
        std::cout << ANSI_COLOR_RED << "Invalid soc. Please enter a positive number." << ANSI_COLOR_DEFAULT << std::endl;
        std::cout << "Enter battery state of charge (SOC) (0-100): ";
        std::cin >> soc;
    }

    std::cout << "Enter battery state of health (SOH) (0-100): ";
    std::cin >> soh;
    while (soh < 0 || soh > 100)
    {
        std::cout << ANSI_COLOR_RED << "Invalid soh. Please enter a positive number." << ANSI_COLOR_DEFAULT << std::endl;
        std::cout << "Enter battery state of health (SOH) (0-100): ";
        std::cin >> soh;
    }

    std::cout << "Enter battery staus (0: CHARGING, 1: READY, 2:MAINTENANCE, 3:RENTED): ";
    int status_input;
    std::cin >> status_input;
    while (status_input < 0 || status_input > 3)
    {
        std::cout << ANSI_COLOR_RED << "Invalid status input. Please enter a positive number." << ANSI_COLOR_DEFAULT << std::endl;
        std::cout << "Enter battery staus (0: CHARGING, 1: READY, 2:MAINTENANCE, 3:RENTED): ";
        std::cin >> status_input;
    }

    switch (status_input)
    {
    case 0:
        status = STATUS_CHARGING;
        break;
    case 1:
        status = STATUS_READY;
        break;
    case 2:
        status = STATUS_MAINTENANCE;
        break;
    case 3:
        status = STATUS_RENTED;
        break;
    default:
        status = STATUS_RENTED;
        break;
    }

    return new Battery(type, capacity_KWh, soc, soh, status);
}

std::string batteryUpdateMenu()
{
    std::cout << "1. update battery type: " << std::endl;
    std::cout << "2. battery capacity (KWh): " << std::endl;
    std::cout << "3. battery state of charge (SOC) (0-100): " << std::endl;
    std::cout << "4. battery state of health (SOH) (0-100): " << std::endl;
    std::cout << "5. battery staus (0: CHARGING, 1: READY, 2:MAINTENANCE, 3:RENTED): " << std::endl;
    std::cout << ANSI_COLOR_RED << "6. done" << ANSI_COLOR_DEFAULT << std::endl;

    std::string choice;
    while (true)
    {
        std::cin >> choice;
        if (choice == "1" ||
            choice == "2" ||
            choice == "3" ||
            choice == "4" ||
            choice == "5" ||
            choice == "6")
            break;
        else
            std::cout << ANSI_COLOR_RED << "invalid option. try again!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return choice;
}

int getOldBatterySoCMenu()
{
    int soc;
    std::cout << ANSI_COLOR_YELLOW << "=== Battery Swap ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::cout << "Enter the current State of Charge (SoC) of your depleted battery (0-100%): ";

    while (true)
    {
        std::cin >> soc;
        if (soc >= 0 && soc <= 100)
        {
            break;
        }
        else
        {
            std::cout << ANSI_COLOR_RED << "Invalid SoC. Please enter a number between 0 and 100: " << ANSI_COLOR_DEFAULT;
        }
    }

    return soc;
}

struct Battery *selectBatteryForSwapMenu(const struct Database &db)
{
    if (db.batteries.empty())
    {
        std::cout << ANSI_COLOR_RED << "No batteries available for swap." << ANSI_COLOR_DEFAULT << std::endl;
        return nullptr;
    }

    std::cout << ANSI_COLOR_YELLOW << "\n=== Available Batteries for Swap ===" << ANSI_COLOR_DEFAULT << std::endl;
    std::cout << ANSI_COLOR_YELLOW << std::left
              << std::setw(6) << "ID"
              << std::setw(15) << "Type"
              << std::setw(15) << "Capacity(kWh)"
              << std::setw(8) << "SOC(%)"
              << std::setw(8) << "SOH(%)"
              << ANSI_COLOR_DEFAULT << std::endl;

    std::cout << ANSI_COLOR_YELLOW << std::string(52, '-') << ANSI_COLOR_DEFAULT << std::endl;

    // Display only ready batteries with 100% SoC
    for (auto &pair : db.batteries)
    {
        int id = pair.first;
        Battery *battery = pair.second;

        if (battery->status == STATUS_READY && battery->soc == 100)
        {
            std::cout << ANSI_COLOR_PURPLE << std::left
                      << std::setw(6) << id
                      << std::setw(15) << battery->type
                      << std::setw(15) << battery->capacity_KWh
                      << std::setw(8) << battery->soc
                      << std::setw(8) << battery->soh
                      << ANSI_COLOR_DEFAULT << std::endl;
        }
    }

    int selectedId;
    std::cout << "\nEnter battery ID to swap with: ";

    while (true)
    {
        std::cin >> selectedId;

        if (db.batteries.find(selectedId) != db.batteries.end())
        {
            Battery *selectedBattery = db.batteries.at(selectedId);
            if (selectedBattery->status == STATUS_READY && selectedBattery->soc == 100)
            {
                return selectedBattery;
            }
            else
            {
                std::cout << ANSI_COLOR_RED << "Battery " << selectedId
                          << " is not available. Please select a valid battery: " << ANSI_COLOR_DEFAULT;
            }
        }
        else
        {
            std::cout << ANSI_COLOR_RED << "Battery ID " << selectedId
                      << " does not exist. Please try again: " << ANSI_COLOR_DEFAULT;
        }
    }

    return nullptr;
}