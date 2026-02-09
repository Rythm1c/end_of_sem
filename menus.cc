#include "headers/menus.h"
#include "headers/database.h"
#include "headers/battery.h"
#include "headers/driver.h"
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
        if (choice == "1" || choice == "2" || choice == "3")
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

        if (choice == "1" || choice == "2" || choice == "3" || choice == "4")
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
    std::cout << ANSI_COLOR_YELLOW << "=== Admin Register Menu ===" << ANSI_COLOR_DEFAULT << std::endl;
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

    std::cout << "1. list available batteries" << std::endl;
    std::cout << "2. list EV drivers" << std::endl;
    std::cout << "3. create driver account" << std::endl;
    std::cout << "4. manage batteries" << std::endl;
    std::cout << ANSI_COLOR_RED << "5. logout" << ANSI_COLOR_DEFAULT << std::endl;

    std::string choice;

    while (true)
    {
        std::cin >> choice;
        if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
            break;
        else
            std::cout << ANSI_COLOR_RED << "invalid option. try again!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return choice;
}

void listBatteriesMenu(const Database &db)
{
    std::cout << ANSI_COLOR_YELLOW << std::left
              << std::setw(6) << "ID"
              << std::setw(15) << "Type"
              << std::setw(15) << "Capacity(kWh)"
              << std::setw(8) << "SOC(%)"
              << std::setw(8) << "SOH(%)"
              << std::setw(15) << "Status"
              << ANSI_COLOR_DEFAULT << std::endl;

    std::cout << ANSI_COLOR_YELLOW << std::string(67, '-') << ANSI_COLOR_DEFAULT << std::endl;

    if (db.batteries.empty())
    {
        std::cout << ANSI_COLOR_PURPLE << "No batteries available." << ANSI_COLOR_DEFAULT << std::endl;
    }
    else
    {
        for (auto &pair : db.batteries)
        {
            int id = pair.first;
            Battery *battery = pair.second;

            std::string status_str;
            switch (battery->status)
            {
            case STATUS_CHARGING:
                status_str = "Charging";
                break;
            case STATUS_READY:
                status_str = "Ready";
                break;
            case STATUS_MAINTENANCE:
                status_str = "Maintenance";
                break;
            case STATUS_RENTED:
                status_str = "Rented";
                break;
            default:
                status_str = "Unknown";
            }

            std::cout << ANSI_COLOR_PURPLE << std::left
                      << std::setw(6) << id
                      << std::setw(15) << battery->type
                      << std::setw(15) << battery->capacity_KWh
                      << std::setw(8) << battery->soc
                      << std::setw(8) << battery->soh
                      << std::setw(15) << status_str
                      << ANSI_COLOR_DEFAULT << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Press Enter to return to admin menu...";
    std::cin.ignore();
    std::cin.get();
}

void listDriversMenu(const Database &db)
{
    std::cout << ANSI_COLOR_YELLOW << std::left
              << std::setw(6) << "ID"
              << std::setw(20) << "Name"
              << std::setw(20) << "License Plate"
              << std::setw(12) << "Credits"
              << ANSI_COLOR_DEFAULT << std::endl;

    std::cout << ANSI_COLOR_YELLOW << std::string(58, '-') << ANSI_COLOR_DEFAULT << std::endl;

    if (db.drivers.empty())
    {
        std::cout << ANSI_COLOR_PURPLE << "No drivers available." << ANSI_COLOR_DEFAULT << std::endl;
    }
    else
    {
        for (auto &pair : db.drivers)
        {
            int id = pair.first;
            Driver *driver = pair.second;

            std::cout << ANSI_COLOR_PURPLE << std::left
                      << std::setw(6) << id
                      << std::setw(20) << driver->name
                      << std::setw(20) << driver->plate
                      << std::setw(12) << std::fixed << std::setprecision(2) << driver->credits
                      << ANSI_COLOR_DEFAULT << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Press Enter to return to admin menu...";
    std::cin.ignore();
    std::cin.get();
}