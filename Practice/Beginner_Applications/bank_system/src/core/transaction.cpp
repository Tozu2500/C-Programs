#include "transaction.h"
#include <sstream>
#include <stdexcept>

std::string Transaction::serialize() const {
    std::ostringstream oss;
    oss << id << "|"
        << accountId << "|"
        << (int)type << "|"
        << amount << "|"
        << balanceAfter << "|"
        << (long long)timestamp << "|"
        << relatedAccountId;
    return oss.str();
}

Transaction Transaction::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    Transaction t;

    auto next = [&]() {
        std::getline(iss, token, '|');
        return token;
    };

    t.id = std::stoi(next());
    t.accountId = next();
    t.type = (TransactionType)std::stoi(next());
    t.amount = std::stod(next());
    t.balanceAfter = std::stod(next());
    t.description = next();
    t.timestamp = (std::time_t)std::stoll(next());
    t.relatedAccountId = next();

    return t;
}