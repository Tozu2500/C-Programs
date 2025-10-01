#pragma once
#include <string>

struct Transaction
{
    long long id;
    std::string date;
    double amount;
    std::string category;
    std::string note;
    std::string account;
    bool recurring;
    std::string recurrence;

    Transaction();
    std::string serialize() const;
    static Transaction deserialize(const std::string &line);
};
