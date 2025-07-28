#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

class Calculator {
private:
    double memory;
    std::vector<std::string> history;
    bool angleInRadians;

public:
    Calculator();
    ~Calculator();

    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    double power(double base, double exponent);
    double squareRoot(double value);
    double sine(double angle);
    double cosine(double angle);
    double tangent(double angle);
    double logarithm(double value);
    double naturalLog(double value);
    double factorial(int n);

    void memoryStore(double value);
    double memoryRecall();
    void memoryClear();
    void memoryAdd(double value);
    void memorySubtract(double value);

    void setAngleMode(bool radians);
    bool getAngleMode() const;

    void addToHistory(const std::string& operation);
    void clearHistory();
    std::vector<std::string> getHistory() const;

    double evaluateExpression(const std::string& expression);
};

#endif