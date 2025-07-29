#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <vector>

class Calculator;

enum TokenType {
    NUMBER,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN,
    FUNCTION,
    END_OF_INPUT
};

struct Token {
    TokenType type;
    std::string value;
    double numValue;

    Token(TokenType t, const std::string& v, double n = 0.0)
        : type(t), value(v), numValue(n) {}
};

class ExpressionParser {
private:
    std::vector<Token> tokens;
    size_t currentIndex;
    Calculator* calc;

    void tokenize(const std::string& expression);
    double parseExpression();
    double parseTerm();
    double parseFactor();
    double parseFunction(const std::string& funcName);
    bool isFunction(const std::string& str);
    int getOperatorPrecedence(const std::string& op);

public:
    ExpressionParser();
    double parse(const std::string& expression, Calculator& calculator);
};

#endif // EXPRESSION_PARSER_H