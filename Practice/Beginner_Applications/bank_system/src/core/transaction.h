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
    }
}