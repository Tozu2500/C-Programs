#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <vector>
#include <memory>

class Bank {
private:
    std::vector<std::shared_ptr<Account>> accounts;
    int nextAccountNumber;

public:
    Bank();

    void createAccount(const std::string& holder, double initialBalance = 0.0);
    std::shared_ptr<Account> findAccount(int accountNumber);
    void displayAllAccounts() const;

    void performDeposit(int accountNumber);
    void performWithdrawal(int accountNumber);
    void checkBalance(int accountNumber);
};

#endif