#include "AppState.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

using namespace std;

AppState::AppState()
{
    default_interest_rate = 0.07;
}

void AppState::save(const string &fname)
{
    ofstream ofs(fname);
    if (!ofs) return;
    ofs << "#EXPTDATA\n";
    ofs << "INTEREST:" << default_interest_rate << "\n";
    for (auto &p : accounts) ofs << p.second.serialize() << "\n";
    for (auto &g : goals) ofs << g.serialize() << "\n";
    for (auto &t : transactions) ofs << t.serialize() << "\n";
}

void AppState::load(const string &fname)
{
    ifstream ifs(fname);
    if (!ifs) return;
    accounts.clear();
    transactions.clear();
    goals.clear();
    string line;
    
    while (getline(ifs, line))
    {
        if (line.empty()) continue;
        if (line.rfind("INTEREST:", 0) == 0)
        {
            default_interest_rate = parse_double(line.substr(9));
        }
        else if (line.rfind("ACC:", 0) == 0)
        {
            Account a = Account::deserialize(line);
            if (!a.name.empty()) accounts[a.name] = a;
        }
        else if (line.rfind("GOAL:", 0) == 0)
        {
            Goal g = Goal::deserialize(line);
            if (!g.name.empty()) goals.push_back(g);
        }
        else if (line.rfind("TID=", 0) == 0)
        {
            Transaction t = Transaction::deserialize(line);
            transactions.push_back(t);
        }
    }
}