#include "CLI.h"
#include "Reports.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

void show_accounts(const AppState &S)
{
    cout << "\nAccounts:\n";
    for (auto &kv : S.accounts)
    {
        cout << " - " << kv.first << ": " << fixed << setprecision(2) << kv.second.balance << "\n";
    }
}

void list_transactions(const AppState &S)
{
    cout << "\nTransactions:\n";
    for (auto &t : S.transactions)
    {
        cout << "[" << t.id << "] " << t.date << " " << setw(10) << t.amount << " " << t.category << " (" << t.account << ")";
        if (!t.note.empty()) cout << " - " << t.note;
        if (t.recurring) cout << " [recurs:" << t.recurrence << "]";
        cout << "\n";
    }
}

Transaction input_transaction(const AppState &S)
{
    Transaction t;
    t.id = next_id();
    cout << "Date (YYYY-MM-DD) [default " << now_date() << "]: ";
    string tmp;
    getline(cin, tmp);
    if (trim(tmp).empty()) t.date = now_date();
    else t.date = trim(tmp);
    cout << "Amount (positive income, negative expense): ";
    getline(cin, tmp);
    t.amount = parse_double(trim(tmp));
    cout << "Category: ";
    getline(cin, t.category);
    cout << "Note: ";
    getline(cin, t.note);
    cout << "Account (existing or new): ";
    getline(cin, t.account);
    if (S.accounts.find(t.account) == S.accounts.end())
    {
        cout << "Account not found. Creating new with a balance of zero\n";
    }
    cout << "Recurring? (y/n): ";
    getline(cin, tmp);
    if (!tmp.empty() && (tmp[0] == 'y' || tmp[0] == 'Y'))
    {
        t.recurring = true;
        cout << "Recurrence interval (monthly/yearly/weekly): ";
        getline(cin, t.recurrence);
        if (t.recurrence.empty()) t.recurrence = "monthly";
    }
    else
    {
        t.recurring = false;
        t.recurrence = "none";
    }
    return t;
}

int main_loop(AppState &S)
{
    while (true)
    {
        cout << "\nMenu\n";
        cout << "1. Show accounts\n";
        cout << "2. List transactions\n";
        cout << "3. Add transaction\n";
        cout << "4. Monthly summary\n";
        cout << "5. Projection report\n";
        cout << "6. Export CSV\n";
        cout << "7. Save and exit\n";
        cout << "Choice: ";
        string choice;
        getline(cin, choice);
        if (choice == "1")
        {
            show_accounts(S);
        }
        else if (choice == "2")
        {
            list_transactions(S);
        }
        else if (choice == "3")
        {
            Transaction t = input_transaction(S);
            S.transactions.push_back(t);
            if (S.accounts.find(t.account) == S.accounts.end())
            {
                S.accounts[t.account] = Account(t.account, 0.0);
            }
            S.accounts[t.account].balance += t.amount;
        }
        else if (choice == "4")
        {
            cout << "Enter year-month (YYYY-MM): ";
            string ym;
            getline(cin, ym);
            monthly_summary(S, ym);
        }
        else if (choice == "5")
        {
            cout << "Years to project: ";
            string tmp;
            getline(cin, tmp);
            int years = stoi(tmp);
            cout << "Annual contribution: ";
            getline(cin, tmp);
            double contrib = parse_double(tmp);
            projection_report(S, years, S.default_interest_rate, contrib);
        }
        else if (choice == "6")
        {
            export_csv(S);
            cout << "Exported to export.csv\n";
        }
        else if (choice == "7")
        {
            S.save();
            cout << "Saved. Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
