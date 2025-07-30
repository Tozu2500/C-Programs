#include "expression_parser.h"
#include "calculator.h"
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cmath>

ExpressionParser::ExpressionParser() : currentIndex(0), calc(nullptr) {}

double ExpressionParser::parse(const std::string& expression, Calculator& calculator) {
    calc = &calculator;
    tokens.clear();
    currentIndex = 0;

    tokenize(expression);
    if (tokens.empty()) {
        throw std::invalid_argument("Empty expression");
    }

    double result = parseExpression();

    if (currentIndex < tokens.size() && tokens[currentIndex].type != END_OF_INPUT) {
        throw std::invalid_argument("Unexpected token after expression");
    }

    return result;
}

void ExpressionParser::tokenize(const std::string& expression) {
    size_t i = 0;
    
    while (i < expression.length()) {
        char c = expression[i];
        
        if (std::isspace(c)) {
            i++;
            continue;
        }
        
        if (std::isdigit(c) || c == '.') {
            std::string numStr;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                numStr += expression[i++];
            }
            double value = std::stod(numStr);
            tokens.push_back(Token(NUMBER, numStr, value));
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.push_back(Token(OPERATOR, std::string(1, c)));
            i++;
        }
        else if (c == '(') {
            tokens.push_back(Token(LEFT_PAREN, "("));
            i++;
        }
        else if (c == ')') {
            tokens.push_back(Token(RIGHT_PAREN, ")"));
            i++;
        }
        else if (std::isalpha(c)) {
            std::string funcName;
            while (i < expression.length() && std::isalpha(expression[i])) {
                funcName += expression[i++];
            }
            if (isFunction(funcName)) {
                tokens.push_back(Token(FUNCTION, funcName));
            } else {
                throw std::invalid_argument("Unknown function: " + funcName);
            }
        }
        else {
            throw std::invalid_argument("Invalid character: " + std::string(1, c));
        }
    }
    
    tokens.push_back(Token(END_OF_INPUT, ""));
}

double ExpressionParser::parseExpression() {
    double result = parseTerm();

    while (currentIndex < tokens.size() &&
    tokens[currentIndex].type == OPERATOR &&
    (tokens[currentIndex].value == "+" || tokens[currentIndex].value == "-")) {
        std::string op = tokens[currentIndex].value;
        currentIndex++;
        double right = parseTerm();

        if (op == "+") {
            result = calc->add(result, right);
        } else {
            result = calc->subtract(result, right);
        }
    }

    return result;
}

double ExpressionParser::parseTerm() {
    double result = parseFactor();

    while (currentIndex < tokens.size() &&
    tokens[currentIndex].type == OPERATOR &&
    (tokens[currentIndex].value == "*" || tokens[currentIndex].value == "/")) {
        std::string op = tokens[currentIndex].value;
        currentIndex++;
        double right = parseFactor();

        if (op == "*") {
            result = calc->multiply(result, right);
        } else {
            result = calc->divide(result, right);
        }
    }

    return result;
}

double ExpressionParser::parseFactor() {
    if (currentIndex >= tokens.size()) {
        throw std::invalid_argument("Unexpected end of expression");
    }

    Token& token = tokens[currentIndex];

    if (token.type == NUMBER) {
        currentIndex++;
        return token.numValue;
    }

    if (token.type == OPERATOR && token.value == "-") {
        currentIndex++;
        return -parseFactor();
    }

    if (token.type == LEFT_PAREN) {
        currentIndex++;
        double result = parseExpression();
        if (currentIndex >= tokens.size() || tokens[currentIndex].type != RIGHT_PAREN) {
            throw std::invalid_argument("Missing closing parenthesis");
        }
        currentIndex++;
        return result;
    }

    if (token.type == FUNCTION) {
        return parseFunction(token.value);
    }

    if (token.type == OPERATOR && token.value == "^") {
        currentIndex++;
        double base = parseFactor();
        double exponent = parseFactor();
        return calc->power(base, exponent);
    }

    throw std::invalid_argument("Unexpected token: " + token.value);
}

double ExpressionParser::parseFunction(const std::string& funcName) {
    currentIndex++;

    if (currentIndex >= tokens.size() || tokens[currentIndex].type != LEFT_PAREN) {
        throw std::invalid_argument("Function requires parentheses");
    }
    currentIndex++;

    double arg = parseExpression();

    if (currentIndex >= tokens.size() || tokens[currentIndex].type != RIGHT_PAREN) {
        throw std::invalid_argument("Missing closing parenthesis for function");
    }
    currentIndex++;

    if (funcName == "sin") return calc->sine(arg);
    if (funcName == "cos") return calc->cosine(arg);
    if (funcName == "tan") return calc->tangent(arg);
    if (funcName == "sqrt") return calc->squareRoot(arg);
    if (funcName == "log") return calc->logarithm(arg);
    if (funcName == "ln") return calc->naturalLog(arg);
    if (funcName == "fact") return calc->factorial(static_cast<int>(arg));

    throw std::invalid_argument("Unknown function: " + funcName);
}

bool ExpressionParser::isFunction(const std::string& str) {
    return str == "sin" || str == "cos" || str == "tan" || 
           str == "sqrt" || str == "log" || str == "ln" || str == "fact";
}

int ExpressionParser::getOperatorPrecedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}