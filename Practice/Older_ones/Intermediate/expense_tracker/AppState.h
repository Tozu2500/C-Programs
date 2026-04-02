#pragma once
#include <map>
#include <vector>
#include "Transaction.h"
#include "Account.h"
#include "Goal.h"

struct AppState
{
    std::map<std::string, Account> accounts;
    std::vector<Transaction> transactions;
    std::vector<Goal> goals;
    double default_interest_rate;
    AppState();
    void save(const std::string &fname = "data_store.txt");
    void load(const std::string &fname = "data_store.txt");
};