#include "Goal.h"
#include "Utils.h"
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

string Goal::serialize() const
{
    ostringstream ss;
    ss << "GOAL:" << name;
    ss << ':' << fixed << setprecision(2) << target_amount;
    ss << ':' << target_date;
    ss << ':' << current_saved;
    return ss.str();
}

Goal Goal::deserialize(const string &s)
{
    Goal g;
    vector<string> parts;
    string cur;
    for (char c : s)
    {
        if (c == ':')
        {
            parts.push_back(cur);
            cur.clear();
        }
        else cur.push_back(c);
    }
    parts.push_back(cur);
    if (parts.size() >= 4)
    {
        g.name = parts[1];
        g.target_amount = parse_double(parts[2]);
        g.target_date = parts[3];
        if (parts.size() >= 5) g.current_saved = parse_double(parts[4]);
    }
    return g;
}