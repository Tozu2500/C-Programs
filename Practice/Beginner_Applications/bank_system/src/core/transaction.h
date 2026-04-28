#pragma once
#include <string>
#include <ctime>

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER_IN,
    TRANSFER_OUT,
    INTEREST,
    FEE,
    ACCOUNT_OPEN,
    ACCOUNT_CLOSE
};

inline std::string transactionTypeToString(TransactionType t) {
    switch (t) {
        case TransactionType::DEPOSIT: return "Deposit";
        case TransactionType::WITHDRAWAL: return "Withdrawal";
        case TransactionType::TRANSFER_IN: return "Transfer In";
        case TransactionType::TRANSFER_OUT: return "Transfer Out";
        case TransactionType::INTEREST: return "Interest";
        case TransactionType::FEE: return "Fee";
        case TransactionType::ACCOUNT_OPEN: return "Account Opened";
        case TransactionType::ACCOUNT_CLOSE: return "Account Closed";
        default: return "Unknown";
    }
}

struct Transaction {
    int         id;
    std::string accountId;
    TransactionType type;
    double      amount;
    double      balanceAfter;
    std::string description;
    std::time_t timestamp;
    std::string relatedAccountId; // for transfers

    Transaction() = default;
    Transaction(int id, const std::string& accId, TransactionType type,
                double amount, double balanceAfter,
                const std::string& desc = "",
                const std::string& relatedAcc = "")
        : id(id), accountId(accId), type(type), amount(amount),
          balanceAfter(balanceAfter), description(desc),
          timestamp(std::time(nullptr)), relatedAccountId(relatedAcc) {}

    std::string serialize() const;
    static Transaction deserialize(const std::string& line);
};
