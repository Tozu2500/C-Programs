#include "Utils.h"

using namespace std;

string now_date()
{
    auto t = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(t);
    tm tm = *localtime(&tt);
    char buf[32];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return string(buf);
}

string trim(const string &s)
{
    size_t a = s.find_first_not_of(" \t\n\r");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\n\r");
    return s.substr(a, b - a + 1);
}

double parse_double(const string &s)
{
    try
    {
        return stod(s);
    }
    catch (...)
    {
        return 0.0;
    }
}

long long next_id()
{
    static long long id = 1000;
    id++;
    return id;
}