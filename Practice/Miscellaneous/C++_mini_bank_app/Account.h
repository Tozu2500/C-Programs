#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    int accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(int accNum, const std::string& holder, double initialBalance = 0.0);

    int getAccountNumber() const;
    std::string getAccountHolder() const;
    double getBalance() const;

    bool deposit(double amount);
    bool withdraw(double amount);
    void displayInfo() const;
};

#endif // ACCOUNT_H