#ifndef ADMIN_H
#define ADMIN_H

#include <string>

struct Administrator
{
    std::string name;
    std::string password;

    Administrator(const std::string &name, const std::string &password)
        : name(name), password(password) {}

    Administrator() : name(""), password("") {}

    void rename(const std::string &);

    void resetPassword(const std::string &);
};

#endif