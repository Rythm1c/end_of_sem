#include "headers/menus.h"
#include "headers/database.h"
#include <iostream>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_DEFAULT "\x1b[0m"

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
            std::cout << ANSI_COLOR_RED << "Invalid choice. Please try again!" << ANSI_COLOR_DEFAULT << std::endl;
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
            break;

        std::cout << ANSI_COLOR_RED << "invalid login details!\n"
                  << "username or password wrong!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return p_admin;
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
            std::cout << ANSI_COLOR_RED << "invalid option. try again!" << ANSI_COLOR_DEFAULT << std::endl;
    }

    return choice;
}