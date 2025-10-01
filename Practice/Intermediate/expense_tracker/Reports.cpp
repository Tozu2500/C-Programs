#include "Reports.h"
#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

double future_value_compound(double principal, double annual_rate, int years, int compounds_per_year = 1)
{
    if (years <= 0) return principal;
    double r = annual_rate / compounds_per_year;
    double n = compounds_per_year * years;
    return principal * pow(1.0 + r, n);
}

double fv_with_contrib(double present, double annual_rate, int years, double contrib_per_year, int compounds_per_year = 1)
{
    if (years <= 0) return present + contrib_per_year * years;
    double r = annual_rate / compounds_per_year;
    int n = compounds_per_year * years;
    double contrib_per_period = contrib_per_year / compounds_per_year;
    double fv_present = present * pow(1.0 + r, n);
    double fv_contribs = contrib_per_period * ((pow(1.0 + r, n) - 1.0) / r);
    return fv_present + fv_contribs;
}

void projection_report(const AppState &S, int years, double expected_annual_return, double annual_contribution)
{
    cout << "\nProjection for " << years << " year(s) with expected annual return " << expected_annual_return * 100 << "%\n";
    double total_now = 0.0;
    for (auto &p : S.accounts) total_now += p.second.balance;
    cout << "Current total across accounts: " << fixed << setprecision(2) << total_now << "\n";
    double fv = fv_with_contrib(total_now, expected_annual_return, years, annual_contribution, 1);
    cout << "Projected total after " << years << " years (annual contributions " << annual_contribution << ") : " << fixed << setprecision(2) << fv << "\n";
}

void monthly_summary(const AppState &S, const string &year_month)
{
    double income = 0;
    double expense = 0;
    map<string, double> by_category;
    for (auto &t : S.transactions)
    {
        if (t.date.rfind(year_month, 0) == 0)
        {
            if (t.amount >= 0) income += t.amount;
            else expense += -t.amount;
            by_category[t.category] += t.amount;
        }
    }
    cout << "\nSummary for " << year_month << ":\n";
    cout << "Income: " << fixed << setprecision(2) << income << "\n";
    cout << "Expense: " << fixed << setprecision(2) << expense << "\n";
    cout << "Net: " << fixed << setprecision(2) << income - expense << "\n";
    cout << "By cateogry:\n";
    for (auto &kv : by_category) cout << " " << kv.first << ": " << kv.second << "\n";
}

void export_csv(const AppState &S, const string &fname)
{
    ofstream ofs(fname);
    if (!ofs) return;
    ofs << "id,date,amount,category,note,account,recurring,recurrence\n";
    for (auto &t : S.transactions)
    {
        string n = t.note;
        if (n.find(",") != string::npos || n.find('"') != string::npos)
        {
            string tmp;
            for (char c : n)
            {
                if (c == '"') tmp += '"';
                tmp += c;
            }
            n = '"' + tmp + '"';
        }
        ofs << t.id << ',' << t.date << ',' << t.amount << ',' << '"' << t.category <<
        '"' << ',' << n << ',' << '"' << t.account << '"' << ',' << (t.recurring ? "1" : "0") <<
        ',' << t.recurrence << '\n';
    }
}