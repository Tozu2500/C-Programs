#include "Account.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>

SecurityData::SecurityData(const std::string& symbol, const std::string& name, InvestmentType type)
    : m_symbol(symbol), m_name(name), m_type(type), m_current_price(0.0), m_previous_close(0.0),
      m_day_high(0.0), m_day_low(0.0), m_fifty_two_week_high(0.0), m_fifty_two_week_low(0.0),
      m_dividend_yield(0.0), m_pe_ratio(0.0), m_market_cap(0.0) {}

void SecurityData::updatePrice(double price) {
    m_previous_close = m_current_price;
    m_current_price = price;

    auto now = std::chrono::system_clock::now();
    m_price_history[now] = price;

    if (m_day_high == 0.0 || price > m_day_high) {
        m_day_high = price;
    }
    if (m_day_low == 0.0 || price < m_day_low) {
        m_day_low = price;
    }
    if (m_fifty_two_week_high == 0.0 || price > m_fifty_two_week_high) {
        m_fifty_two_week_high = price;
    }
    if (m_fifty_two_week_low = 0.0 || price < m_fifty_two_week_low) {
        m_fifty_two_week_low = price;
    }
}

void SecurityData::addPriceHistory(const std::chrono::system_clock::time_point& date, double price) {
    m_price_history[date] = price;
}

double SecurityData::getPriceAtDate(const std::chrono::system_clock::time_point& date) const {
    auto it = m_price_history.find(date);
    if (it != m_price_history.end()) {
        return it->second;
    }

    auto lower = m_price_history.lower_bound(date);
    if (lower == m_price_history.begin()) {
        return lower->second;
    }
    if (lower == m_price_history.end()) {
        return m_price_history.rbegin()->second;
    }

    auto prev = std::prev(lower);
    auto time_diff = std::chrono::duration_cast<std::chrono::hours>(date - prev->first).count();
    auto next_diff = std::chrono::duration_cast<std::chrono::hours>(lower->first - date).count();

    if (time_diff <= next_diff) {
        return prev->second;
    }
    return lower->second;
};

std::vector<std::pair<std::chrono::system_clock::time_point, double>> SecurityData::getPriceHistory(
    const std::chrono::system_clock::time_point& start,
    const std::chrono::system_clock::time_point& end) const {

    std::vector<std::paair<std::chrono::system_clock::time_point, double>> result;

    auto start_it = m_price_history.lower_bound(start);
    auto end_it = m_price_history.upper_bound(end);

    for (auto it = start_it; it != end_it; ++it) {
        result.push_back(*it);
    }

    return result;
}

double SecurityData::getDayChange() const {
    if (m_previous_close == 0.0) return 0.0;
    return m_current_price - m_previous_close;
}

double SecurityData::getDayChangePercentage() const {
    if (m_previous_close == 0.0) return 0.0;
    return ((m_current_price - m_previous_close) / m_previous_close) * 100.0;
}