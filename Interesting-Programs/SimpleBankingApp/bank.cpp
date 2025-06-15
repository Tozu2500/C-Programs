#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

class BankAccount {
    private:
        std::string accountNumber;
        std::string accountHolder;

        double balance;

    public:
        // Constructor
        BankAccount(std::string accNum, std::string holder, double initialBalance = 0.0)
            : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {}

        // Getters
        std::string getAccountNumber() const {
            return accountNumber;
        }

        std::string getAccountHolder() const {
            return accountHolder;
        }

        double getBalance() const {
            return balance;
        }

    // Deposit
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Successfully deposited $" << std::fixed << std::setprecision(2) << amount << std::endl;
            return true;
        }
        std::cout << "Invalid deposit amount!" << std::endl;
        return false;
    }

    // Withdraw
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Successfully withdrew $" << std::fixed << std::setprecision(2) << amount << std::endl;
            return true;
        } else if (amount > balance) {
            std::cout << "Insufficient funds!" << std::endl;
        } else {
            std:: cout << "Invalid withdrawal amount!" << std::endl;
        }
        return false;
    }

    // Display account info
    void displayAccount() const {
        std::cout << "\n ___ Account Information ___" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "----------------------------------\n" << std::endl;
    }
};

class Bank {
    private:
        std::vector<BankAccount> accounts;
        std::string filename;

    public:
        Bank(std::string file) : filename(file) {
            loadAccounts();
        }

        ~Bank() {
            saveAccounts();
        }

    // Create new account
    void createAccount() {
        std::string accNum, holder;
        double initialDeposit;

        std::cout << "Enter account number: ";
        std::cin >> accNum;

        // Check if the entered account already exists
        for (const auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                std::cout << "Account with that number already exists!" << std::endl;
                return;
            }
        }
          // Clear input buffer
        std::cin.ignore();

        std::cout << "Enter account holder name: ";
        std::getline(std::cin, holder);

        std::cout << "Enter initial deposit in $";

        if (initialDeposit < 0) {
            std::cout << "Initial deposit can't be negative" << std::endl;
            return;
        }

        BankAccount newAccount(accNum, holder, initialDeposit);
        accounts.push_back(newAccount);
        std::cout << "Account created successfully!" << std::endl;
    }

    // Find accounts by number
    BankAccount* findAccount(const std::string& accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    // Deposit to account
    void depositToAccount() {
        std::string accNum;
        double amount;

        std::cout << "Enter account number: ";
        std::cin >> accNum;

        BankAccount* account = findAccount(accNum);
        if (account) {
            std::cout << "Enter deposit amount: $";
            std::cin >> amount;
            account->deposit(amount);
        } else {
            std::cout << "Account not found" << std::endl;
        }
    }

    // Withdraw from account
    void withdrawFromAccount() {
        std::string accNum;
        double amount;

        std::cout << "Enter account number: ";
        std::cin >> accNum;

        BankAccount* account = findAccount(accNum);
        if (account) {
            std::cout << "Enter withdrawal amount: $";
            std::cin >> amount;
            account->withdraw(amount);
        } else {
            std::cout << "Account not found" << std::endl;
        }
    }

    // Check balance
    void checkBalance() {
        std::string accNum;

        std::cout << "Enter account number: ";
        std::cin >> accNum;

        BankAccount* account = findAccount(accNum);
        if (account) {
            account->displayAccount();
        } else {
            std::cout << "Account not found" << std::endl;
        }
    }

    // Display all accounts
    void displayAllAccounts() {
        if (accounts.empty()) {
            std::cout << "No accounts exist yet!" << std::endl;
            return;
        }

        std::cout << "\n___ All accounts ___" << std::endl;
        for (const auto& acc : accounts) {
            acc.displayAccount();
        }
    }

    // Save accounts to a file
    void saveAccounts() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& acc : accounts) {
                file << acc.getAccountNumber() << " "
                     << acc.getAccountHolder() << " "
                     << acc.getBalance() << std::endl;
            }
            file.close();
        }
    }

    // Load accounts from a file
    void loadAccounts() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string accNum, holder;
            double balance;

            while (file >> accNum >> holder >> balance) {
                BankAccount account(accNum, holder, balance);
                accounts.push_back(account);
            }
            file.close();
        }
    }
};

void displayMenu() {
    std::cout << "\n--- Basic banking system ---" << std::endl;
    std::cout << "1. Create account" << std::endl;
    std::cout << "2. Deposit money" << std::endl;
    std::cout << "3. Withdraw money" << std::endl;
    std::cout << "4. Check your balance" << std::endl;
    std::cout << "5. Display all existing accounts" << std::endl;
    std::cout << "6. Exit app" << std::endl;
    std::cout << "Choose an option (1-6)";
}

int main() {
    Bank bank("accounts.txt");
    int choice;

    std::cout << "Welcome to a basic banking system" << std::endl;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositToAccount();
                break;
            case 3:
                bank.withdrawFromAccount();
                break;
            case 4:
                bank.checkBalance();
                break;
            case 5:
                bank.displayAllAccounts();
                break;
            case 6:
                std::cout << "Thank you for using the application!" << std::endl;
                return 0;
            default:
                std::cout << "Enter a valid choice!" << std::endl;
        }

        // Pause before re-showing the menu again
        std::cout << "\nPress continue to enter...";
        std::cin.ignore();
        std::cin.get();
    }
    
    return 0;
}