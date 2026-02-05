#include "headers/admin.h"
#include <iostream>

void Administrator::rename(const std::string &newName)
{
    if (newName.empty())
    {
        std::cout << "name cannot be empty!" << std::endl;
        return;
    }
    this->name = newName;
}

void Administrator::resetPassword(const std::string &newPassword)
{
    if (this->password == newPassword)
    {
        std::cout << "New password must be different from the old password!" << std::endl;
        return;
    }

    if (newPassword.empty())
    {
        std::cout << "password cannot be empty!" << std::endl;
        return;
    }

    if (newPassword.length() < 6)
    {
        std::cout << "password cannot be less than 6 characters!" << std::endl;
        return;
    }

    this->password = newPassword;
}