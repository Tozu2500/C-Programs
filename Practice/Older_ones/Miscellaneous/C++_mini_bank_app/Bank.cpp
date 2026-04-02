#include "bank.h"
#include <iostream>
#include <iomanip>

Bank::Bank() : nextAccountNumber(1001) {}

void Bank::createAccount(const std::string& holder, double initialBalance) {
    auto account = std::make_shared<Account>(nextAccountNumber, holder, initialBalance);
    accounts.push_back(account);
    std::cout << "\nYour bank account was created successfully!\n";
    std::cout << "Account Number: " << nextAccountNumber << "\n";
    std::cout << "Account Holder: " << holder << "\n";
    std::cout << "Initial Balance: $" << std::fixed << std::setprecision(2)
            << initialBalance << "\n";
    nextAccountNumber++;
}

std::shared_ptr<Account> Bank::findAccount(int accountNumber) {
    for (auto& account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            return account;
        }
    }
    return nullptr;
}

void Bank::displayAllAccounts() const {
    if (accounts.empty()) {
        std::cout << "\nNo accounts are in the system.\n";
        return;
    }

    std::cout << "\nAll Accounts\n";
    for (const auto& account : accounts) {
        account->displayInfo();
    }
}

void Bank::performDeposit(int accountNumber) {
    auto account = findAccount(accountNumber);
    if (!account) {
        std::cout << "Error, the account wasn't found\n";
        return;
    }

    double amount;
    std::cout << "How much to deposit: $";
    std::cin >> amount;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input\n";
        return;
    }

    account->deposit(amount);
    std::cout << "New account balance: $" << std::fixed << std::setprecision(2)
        << account->getBalance() << "\n";
}

void Bank::performWithdrawal(int accountNumber) {
    auto account = findAccount(accountNumber);
    if (!account) {
        std::cout << "Error, the account wasn't found\n";
        return;
    }

    double amount;
    std::cout << "Enter withdrawal amount: $";
    std::cin >> amount;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input\n";
        return;
    }

    if (account->withdraw(amount)) {
        std::cout << "New account balance: $" << std::fixed << std::setprecision(2)
                << account->getBalance() << "\n";
    }
}

void Bank::checkBalance(int accountNumber) {
    auto account = findAccount(accountNumber);
    if (!account) {
        std::cout << "Error, account wasn't found\n";
        return;
    }

    account->displayInfo();
}