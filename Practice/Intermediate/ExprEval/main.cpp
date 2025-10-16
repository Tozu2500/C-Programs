/*
    Expression Evaluator
    Building an infix expression evaluator using stacks.
    Supporting: +, -, *, /, parentheses, and operator precedence.
*/
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>

class ExpressionEvaluator {
public:
    static double evaluate(const std::string& expression) {
        std::stack<double> values;
        std::stack<char> ops;
        size_t i = 0;
        while (i < expression.length()) {
            if (isspace(expression[i])) {
                ++i;
                continue;
            }
            if (isdigit(expression[i]) || expression[i] == '.') {
                double val = 0;
                int decimal = -1;
                while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                    if (expression[i] == '.') {
                        decimal = 0;
                        ++i;
                        continue;
                    }
                    if (decimal == -1) {
                        val = val * 10 + (expression[i] - '0');
                    } else {
                        ++decimal;
                        val += (expression[i] - '0') / pow(10, decimal);
                    }
                    ++i;
                }
                values.push(val);
            } else if (expression[i] == '(') {
                ops.push(expression[i]);
                ++i;
            } else if (expression[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    applyTopOperator(values, ops);
                }
                if (!ops.empty()) ops.pop(); // pop '('
                ++i;
            } else if (isOperator(expression[i])) {
                while (!ops.empty() && ops.top() != '(' && precedence(ops.top()) >= precedence(expression[i])) {
                    applyTopOperator(values, ops);
                }
                ops.push(expression[i]);
                ++i;
            } else {
                throw std::invalid_argument("Invalid character in expression");
            }
        }
        while (!ops.empty()) {
            applyTopOperator(values, ops);
        }
        if (values.size() != 1) throw std::runtime_error("Invalid expression");
        return values.top();
    }

private:
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    static bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    static void applyTopOperator(std::stack<double>& values, std::stack<char>& ops) {
        if (values.size() < 2 || ops.empty())
            throw std::runtime_error("Invalid expression");
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        double result = 0;
        switch (op) {
            case '+': result = left + right; break;
            case '-': result = left - right; break;
            case '*': result = left * right; break;
            case '/':
                if (right == 0) throw std::runtime_error("Division by zero");
                result = left / right; break;
            default: throw std::runtime_error("Unknown operator");
        }
        values.push(result);
    }
};

int main() {
    std::string expr;
    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, expr);
    try {
        double result = ExpressionEvaluator::evaluate(expr);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    return 0;
}