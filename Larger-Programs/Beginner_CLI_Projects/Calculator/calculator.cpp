#define _USE_MATH_DEFINES
#include "calculator.h"
#include "expression_parser.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

Calculator::Calculator() : memory(0.0), angleInRadians(false) {}

Calculator::~Calculator() {}

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

double Calculator::power(double base, double exponent) {
    return pow(base, exponent);
}

double Calculator::squareRoot(double value) {
    if (value < 0) {
        throw std::invalid_argument("Square root of a negative number is not possible");
    }
    return sqrt(value);
}

double Calculator::sine(double angle) {
    if (!angleInRadians) {
        angle = angle * M_PI / 180.0;
    }
    return sin(angle);
}

double Calculator::cosine(double angle) {
    if (!angleInRadians) {
        angle = angle * M_PI / 180.0;
    }
    return cos(angle);
}

double Calculator::tangent(double angle) {
    if (!angleInRadians) {
        angle = angle * M_PI / 180.0;
    }
    return tan(angle);
}

double Calculator::logarithm(double value) {
    if (value <= 0) {
        throw std::invalid_argument("Logarithm of non-positive number");
    }
    return log10(value);
}

double Calculator::naturalLog(double value) {
    if (value <= 0) {
        throw std::invalid_argument("Natural logarithm of non-positive number");
    }
    return log(value);
}

double Calculator::factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Factorial of a negative number");
    }
    if (n > 20) {
        throw std::invalid_argument("Factorial too large");
    }
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void Calculator::memoryStore(double value) {
    memory = value;
}

double Calculator::memoryRecall() {
    return memory;
}

void Calculator::memoryClear() {
    memory = 0.0;
}

void Calculator::memoryAdd(double value) {
    memory += value;
}

void Calculator::memorySubtract(double value) {
    memory -= value;
}

void Calculator::setAngleMode(bool radians) {
    angleInRadians = radians;
}

bool Calculator::getAngleMode() const {
    return angleInRadians;
}

void Calculator::addToHistory(const std::string& operation) {
    history.push_back(operation);
    if (history.size() > 50) {
        history.erase(history.begin());
    }
}

void Calculator::clearHistory() {
    history.clear();
}

std::vector<std::string> Calculator::getHistory() const {
    return history;
}

double Calculator::evaluateExpression(const std::string& expression) {
    ExpressionParser parser;
    return parser.parse(expression, *this);
}