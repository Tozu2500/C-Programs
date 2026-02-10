#include "bank.h"
#include <iostream>
#include <limits>

void displayMenu() {
    std::cout << "\nSimplebank\n";
    std::cout << "1. Create new account\n";
    std::cout << "2. Deposit money\n";
    std::cout << "3. Withdraw money\n";
    std::cout << "4. Check balance\n";
    std::cout << "5. Display all accounts\n";
    std::cout << "-------------------------------\n";
    std::cout << "Enter your choice: ";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Bank bank;
    int choice;

    std::cout << "Welcome to Simplebank!\n";

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInputBuffer();
            std::cout << "Invalid input, please enter a number\n";
            continue;
        }

        clearInputBuffer();

        switch (choice) {
            case 1: {
                std::string name;
                double initialBalance;

                std::cout << "\nEnter account holder name: ";
                std::getline(std::cin, name);

                std::cout << "Enter initial deposit money: $";
                std::cin >> initialBalance;

                if (std::cin.fail()) {
                    clearInputBuffer();
                    std::cout << "Error, invalid amount!\n";
                    break;
                }

                bank.createAccount(name, initialBalance);
                break;
            }
            case 2: {
                int accountNum;
                std::cout << "\nEnter account number: ";
                std::cin >> accountNum;

                if (std::cin.fail()) {
                    clearInputBuffer();
                    std::cout << "Error, invalid account number\n";
                    break;
                }

                bank.performDeposit(accountNum);
                break;
            }
            case 3: {
                int accountNum;
                std::cout << "\nEnter account number: ";
                std::cin >> accountNum;

                if (std::cin.fail()) {
                    clearInputBuffer();
                    std::cout << "Error, invalid account number\n";
                    break;
                }

                bank.performWithdrawal(accountNum);
                break;
            }
            case 4: {
                int accountNum;
                std::cout << "\nEnter account number: ";
                std::cin >> accountNum;

                if (std::cin.fail()) {
                    clearInputBuffer();
                    std::cout << "Error, invalid account number\n";
                    break;
                }

                bank.checkBalance(accountNum);
                break;
            }
            case 5: {
                bank.displayAllAccounts();
                break;
            }
            case 6:
                std::cout << "\nBye!\n";
                return 0;
            default:
                std::cout << "\nInvalid choice, please try again!\n";
        }
    }

    return 0;
}