#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#include <string>

class Calculator;

class UIHandler {
private:
    Calculator* calc;
    bool running;

    void clearScreen();
    void displayWelcome();
    void displayMenu();
    void displayHistory();
    void displayMemoryStatus();
    void handleBasicOperation();
    void handleScientificOperation();
    void handleMemoryOperation();
    void handleSettings();
    void handleExpressionEvaluation();
    void printSeparator();
    void waitForEnter();

public:
    UIHandler(Calculator* calculator);
    ~UIHandler();

    void run();
    void setCalculator(Calculator* calculator);
};

#endif // UI_HANDLER_H