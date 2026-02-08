#include "Account.h"
#include <iostream>
#include <iomanip>

Account::Account(int accNum, const std::string& holder, double initialBalance)
    : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {
    if (initialBalance < 0) {
        balance = 0.0;
    }
}

int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getAccountHolder() const {
    return accountHolder;
}

double Account::getBalance() const {
    return balance;
}

bool Account::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Error, the deposit amount must be positive.\n";
        return false;
    }

    balance += amount;
    std::cout << "Successfully deposited $" << std::fixed << std::setprecision(2)
            << amount << "\n";
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Error, withdrawal must be positive\n";
        return false;
    }

    if (amount > balance) {
        std::cout << "Error, insufficient funds!\n";
        return false;
    }

    balance -= amount;
    std::cout << "Successfully withdrew $" << std::fixed << std::setprecision(2)
            << amount << "\n";
    return true;
}

void Account::displayInfo() const {
    std::cout << "\nAccount Information\n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Account Holder: " << accountHolder << "\n";
    std::cout << "Balance: $" << balance << std::fixed << std::setprecision(2) << balance << "\n";
}