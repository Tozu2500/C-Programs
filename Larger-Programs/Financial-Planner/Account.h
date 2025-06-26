#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <unordered_map>

enum class AccountType {
    CHECKINGS,
    SAVINGS,
    CREDIT_CARD,
    INVESTMENT,
    RETIREMENT,
    LOAN,
    MORTGAGE
};

enum class TransactionType  {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER,
    PURCHASE,
    PAYMENT,
    DIVIDEND,
    INTEREST,
    FEE
};

class Transaction {
    private:
    std::string m_id;
    double m_amount;
    std::string m_description;
    std::string m_category;
    TransactionType m_type;
    std::chrono::system_clock::time_point m_timestamp;
    std::string m_reference_account;
    std::unordered_map<std::string, std::string> m_metadata;

public:
    Transaction(const std::string& id, double amount, const std::string& description,
                const std::string& cateogry, TransactionType type,
                const std::string& reference_account = "");
    const std::string& getId() const {
        return m_id;
    }

    double getAmount() const {
        return m_amount;
    }

    const std::string& getDescription() const {
        return m_category;
    }

    const std::string& getCategory() const {
        return m_category;
    }

    TransactionType getType() const {
        return m_type;
    }

    const std::chrono::system_clock::time_point& getTimestamp() const {
        return m_timestamp;
    }

    const std::string& getReferenceAccount() const {
        return m_reference_account;
    }

    void setDescription(const std::string& description) {
        m_description = description;
    }

    void setCategory(const std::string& category) {
        m_category = category;
    }

    void addMetadata(const std::string& key, const std::string& value);
    
    std::string getMetadata(const std::string& key) const;

    std::string toString() const;

    bool isWithinDateRange(const std::chrono::system_clock::time_point& start,
            const std::chrono::system_clock::time_point& end) const;
};

class Account {
protected:
    std::string m_id;
    std::string m_name;
    AccountType m_type;
    double m_balance;
    double m_interest_rate;
    std::vector<std::shared_ptr<Transaction>> m_transactions;
    std::chrono::system_clock::time_point m_created_date;
    std::unordered_map<std::string, double> m_monthly_limits;
    bool m_is_active;
public:
    Account (const std::string& id, const std::string& name, AccountType type, double initial_balance = 0.0);
    virtual ~Account() = default;

    const std::string& getId() const {
        return m_id;
    }

    const std::string& getName() const {
        return m_name;
    }

    AccountType getType() const {
        return m_type;
    }

    double getBalance() const {
        return m_balance;
    }

    double getInterestRate() const {
        return m_interest_rate;
    }

    bool isActive() const {
        return m_is_active;
    }

    void setName(const std::string& name) {
        m_name = name;
    }

    void setInterestRate(double rate) {
        m_interest_rate = rate;
    }

    void setActive(bool active) {
        m_is_active = active;
    }

    void setMonthlyLimit(const std::string& category, double limit);

    virtual bool addTransaction(std::shared_ptr<Transaction> transaction);
    virtual bool removeTransaction(const std::string& transaction_id);
    virtual double calculateInterest(int days) const;
    virtual void applyInterest();

    std::vector<std::shared_ptr<Transaction>> getTransactions() const {
        return m_transactions;
    }

    std::vector<std::shared_ptr<Transaction>> getTransactions() const { return m_transactions; }
    std::vector<std::shared_ptr<Transaction>> getTransactionsByCategory(const std::string& category) const;
    std::vector<std::shared_ptr<Transaction>> getTransactionsByDateRange(
        const std::chrono::system_clock::time_point& start,
        const std::chrono::system_clock::time_point& end) const;

    double getMonthlySpending(const std::string& category) const;
    double getTotalSpending() const;
    double getAverageTransactionAmount() const;

    std::string getAccountTypeName() const;
    std::string generateStatement(const std::chrono::system_clock::time_point& start,
                const std::chrono::system_clock::time_point& end) const;

    virtual std::string getAccountDetails() const;
};

class CheckingAccount : public Account {
private:
    double m_overdraft_limit;
    double m_monthly_fee;
    int m_free_transactions_per_month;
    int m_current_month_transactions;

public:
    CheckingAccount(const std::string& id, const std::string& name, double initial_balance = 0.0);

    void setOverdraftLimit(double limit) {
        m_overdraft_limit = limit;
    }
    void setMonthlyFee(double fee) {
        m_monthly_fee = fee;
    }
    void setFreeTransactionsPerMonth(int count) {
        m_free_transactions_per_month = count;
    }

    double getOverdraftLimit() const {
        return m_overdraft_limit;
    }

    double getMonthlyFee() const {
        return m_monthly_fee;
    }

    int getFreeTransactionsPerMonth() const {
        return m_free_transactions_per_month;
    }

    int getCurrentMonthTransactions() const {
        return m_current_month_transactions;
    }

    bool addTransaction(std::shared_ptr<Transaction> transaction) override;
    void processMonthlyFee();
    std::string getAccountDetails() const override;
};

class SavingsAccount : public Account {
private:
    double m_minimum_balance;
    int m_withrawal_limit_per_month;
    int m_current_month_withdrawals;
    double m_penalty_fee;

public:
    SavingsAccount(const std::string& id, const std::string& name, double initial_balance = 0.0);

    void setMinimumBalance(double balance) {
        m_minimum_balance = balance;
    }

    void setWithdrawalLimitPerMonth(int limit) {
        m_withrawal_limit_per_month = limit;
    }

    void setPenaltyFee(double fee) {
        m_penalty_fee = fee;
    }

    double getMinimumBalance() const { return m_minimum_balance; }
    int getWithdrawalLimitPerMonth() const { return m_withrawal_limit_per_month; }
    int getCurrentMonthWithdrawals() const { return m_current_month_withdrawals; }
    double getPenaltyFee() const { return m_penalty_fee; }

    bool addTransaction(std::shared_ptr<Transaction> transaction) override;
    double calculateInterest(int days) const override;
    std::string getAccountDetails() const override;
};

class CreditCardAccount : public Account {
private:
    double m_credit_limit;
    double m_apr;
    double m_minimum_payment_percentage;
    std::chrono::system_clock::time_point m_statement_date;
    std::chrono::system_clock::time_point m_due_date;
    double m_current_statement_balance;

public:
    CreditCardAccount(const std::string& id, const std::string& name, double credit_limit);

    void setCreditLimit(double limit) { m_credit_limit = limit; }
    void setAPR(double apr) { m_apr = apr; }
    void setMinimumPaymentPercentage(double percentage) { m_minimum_payment_percentage = percentage; }
    void setStatementDate(const std::chrono::system_clock::time_point& date) { m_statement_date = date; }
    void setDueDate(const std::chrono::system_clock::time_point& date) { m_due_date = date; }

    double getCreditLimit() const {
        return m_credit_limit;
    }
    double getAPR() const {
        return m_apr;
    }
    double getAvailableCredit() const {
        return m_credit_limit + m_balance;
    }
    double getMinimumPayment() const;
    double getCurrentStatementBalance() const { return m_current_statement_balance; }

    bool addTransaction(std::shared_ptr<Transaction> transaction) override;
    void generateStatement();
    double calculateInterest(int days) const override;
    std::string getAccountDetails() const override;
};

#endif // INVESTMENT_H