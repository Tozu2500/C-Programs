#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>

std::string now_date();
std::string trim(const std::string s&);
double parse_double(const std::string &s);
long long next_id();