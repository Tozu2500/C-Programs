#include "Account.h"
#include "Utils.h"
#include <sstream>
#include <iomanip>

using namespace std;

Account::Account()
{
    name = "";
    balance = 0.00;
}

Account::Account(const string &n, double b)
{
    name = n;
    balance = b;
}

string Account::serialize() const
{
    ostringstream ss;
    ss << "ACC:" << name << ":" << fixed << setprecision(2) << balance;
    return ss.str();
}

Account Account::deserialize(const string &s)
{
    Account a;
    size_t p = s.find(':');
    if (p == string::npos) return a;
    size_t q = s.find(':', p + 1);
    if (q == string::npos) return a;
    a.name = s.substr(p + 1, q - p - 1);
    a.balance = parse_double(s.substr(q + 1));
    return a;
}