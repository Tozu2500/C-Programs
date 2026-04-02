#pragma once
#include <string>

struct Account
{
    std::string name;
    double balance;
    Account();
    Account(const std::string &n, double b);
    std::string serialize() const;
    static Account deserialize(const std::string &s);
};