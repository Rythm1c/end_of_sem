#ifndef DRIVER_H
#define DRIVER_H

#include <string>

struct Driver
{
    std::string name;
    std::string password;
    std::string plate;
    float credits;

    Driver(const std::string &name, const std::string &password, const std::string &licenseNumber, float credits)
        : name(name), password(password), plate(licenseNumber), credits(credits) {}
    Driver() : name(""), password(""), plate(""), credits(0.0) {}
};

#endif