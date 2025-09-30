#include "Transaction.h"
#include "Utils.h"
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

Transaction::Transaction()
{
    id = 0;
    amount = 0.0;
    recurring = false;
    recurrence = "none";
}

string Transaction::serialize() const
{
    auto esc = [](const string &s)
    {
        string r;
        for (char c : s)
        {
            if (c == '|') r += "\\|";
            else r += c;
        }
        return r;
    };
    ostringstream ss;
    ss << "TID=" << id;
    ss << "|DATE=" << date;
    ss << "|AMT=" << fixed << setprecision(2) << amount;
    ss << "|CAT=" << esc(category);
    ss << "|NOTE=" << esc(note);
    ss << "|ACC=" << esc(account);
    ss << "|REC=" << (recurring ? "1" : "0");
    ss << "|RINT" << recurrence;
    return ss.str();
}

Transaction Transaction::deserialize(const string &line)
{
    Transaction t;
    vector<string> parts;
    string cur;
    bool esc = false;
    for (size_t i = 0; i < line.size(); ++i)
    {
        char c = line[i];
        if (esc)
        {
            if (c == '|') cur.push_back('|');
            else if (c == 'n') cur.push_back('\n');
            else cur.push_back(c);
            esc = false;
        }
        else
        {
            if (c == '\\') esc = true;
            else if (c == '|')
            {
                parts.push_back(cur);
                cur.clear();
            }
            else cur.push_back(c);
        }
    }
    if (!cur.empty()) parts.push_back(cur);
    for (auto &p : parts)
    {
        size_t eq = p.find('=');
        if (eq == string::npos) continue;
        string k = p.substr(0, eq);
        string v = p.substr(eq + 1);
        if (k == "TID") t.id = stoll(v);
        else if (k == "DATE") t.date = v;
        else if (k == "AMT") t.amount = parse_double(v);
        else if (k == "CAT") t.category = v;
        else if (k == "NOTE") t.note = v;
        else if (k == "ACC") t.account = v;
        else if (k == "REC") t.recurring = (v == "1");
        else if (k == "RINT") t.recurrence = v;
    }
    return t;
}
