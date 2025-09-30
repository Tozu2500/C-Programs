#pragma once
#include "AppState.h"
#include <string>

void projection_report(const AppState &S, int years, double expected_annual_return, double annual_contribution);
void mothly_summary(const AppState &S, const std::string &year_month);
void export_csv(const AppState &S, const std::string &fname = "export.csv");