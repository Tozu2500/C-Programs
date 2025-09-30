#pragma once
#include <string>

struct Goal
{
    std::string name;
    double target_amount;
    std::string target_date;
    double current_saved;
    std::string serialize() const;
    static Goal deserialize(const std::string &s);
};