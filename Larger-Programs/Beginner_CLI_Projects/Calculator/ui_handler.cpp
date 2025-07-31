#include "ui_handler.h"
#include "calculator.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <windows.h>

UIHandler::UIHandler(Calculator* calculator) : calc(calculator), running(true) {}

UIHandler::~UIHandler() {}

void UIHandler::run() {
    clearScreen();
    displayWelcome();

    while (running) {
        displayMenu();
        displayMemoryStatus();

        int choice;
        std::cout << "\nEnter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
            waitForEnter();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                handleBasicOperation();
                break;
            case 2:
                handleScientificOperation();
                break;
            case 3:
                handleExpressionEvaluation();
                break;
            case 4:
                handleMemoryOperation();
                break;
            case 5:
                displayHistory();
                break;
            case 6:
                handleSettings();
                break;
            case 7:
                running = false;
                std::cout << "Thanks for using the calculator!\n";
                break;
            default:
                std::cout << "Invalid choice, please try again\n";
                waitForEnter();
                break;
        }

        if (running) {
            clearScreen();
        }
    }
}

void UIHandler::clearScreen() {
    system("cls");
}

void UIHandler::displayWelcome() {
    printSeparator();
    std::cout << "  Advanced Calculator - Terminal Windows Version  \n";
    printSeparator();
    std::cout << "\n";
}

void UIHandler::displayMenu() {
    std::cout << "Main Menu\n\n";
    std::cout << "1. Basic Operations (+, -, *, /)\n";
    std::cout << "2. Scientific Operations\n";
    std::cout << "3. Expression Evaluation\n";
    std::cout << "4. Memory Operations\n";
    std::cout << "5. View History\n";
    std::cout << "6. Settings\n";
    std::cout << "7. Exit\n";
}

void UIHandler::displayMemoryStatus() {
    double memValue = calc->memoryRecall();
    std::cout << "\nMemory: " << std::fixed << std::setprecision(6) << memValue;
    std::cout << " | Angle Mode: " << (calc->getAngleMode() ? "Radians" : "Degrees") << "\n";
}

void UIHandler::handleBasicOperation() {
    std::cout << "\nBasic Operations:\n";
    std::cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Power\n";
    std::cout << "Enter operation (1-5): ";

    int op;
    if (!(std::cin >> op) || op < 1 || op > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid operation\n";
        waitForEnter();
        return;
    }

    double a, b;
    std::cout << "Enter first number: ";
    if (!(std::cin >> a)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number!\n";
        waitForEnter();
        return;
    }

    std::cout << "Enter second number: ";
    if (!(std::cin >> b)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number!\n";
        waitForEnter();
        return;
    }

    try {
        double result;
        std::string operation;

        switch (op) {
            case 1:
                result = calc->add(a, b);
                operation = std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(result);
                break;
            case 2:
                result = calc->subtract(a, b);
                operation = std::to_string(a) + " - " + std::to_string(b) + " = " + std::to_string(result);
                break;
            case 3:
                result = calc->multiply(a, b);
                operation = std::to_string(a) + " * " + std::to_string(b) + " = " + std::to_string(result);
                break;
            case 4:
                result = calc->divide(a, b);
                operation = std::to_string(a) + " / " + std::to_string(b) + " = " + std::to_string(result);
                break;
            case 5:
                result = calc->power(a, b);
                operation = std::to_string(a) + " ^ " + std::to_string(b) + " = " + std::to_string(result);
                break;
        }

        calc->addToHistory(operation);
        std::cout << "\nResult: " << std::fixed << std::setprecision(10) << result << "\n";

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    waitForEnter();
}

void UIHandler::handleScientificOperation() {
    std::cout << "\nScientific Operations\n";
    std::cout << "1. Square Root\n2. Sine\n3. Cosine\n4. Tangent\n";
    std::cout << "5. Logarithm (base 10)\n6. Natural Logarithm\n7. Factorial\n";
    std::cout << "Enter operation (1-7): ";

    int op;
    if (!(std::cin >> op) || op < 1 || op > 7) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid operation\n";
        waitForEnter();
        return;
    }

    double value;
    std::cout << "Enter value: ";
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number\n";
        waitForEnter();
        return;
    }

    try {
        double result;
        std::string operation;

        switch (op) {
            case 1:
                result = calc->squareRoot(value);
                operation = "sqrt(" + std::to_string(value) + ") = " + std::to_string(result);
                break;
            case 2:
                result = calc->sine(value);
                operation = "sin(" + std::to_string(value) + ") = " + std::to_string(result);
                break;
            case 3:
                result = calc->cosine(value);
                operation = "cos(" + std::to_string(value) + ") = " + std::to_string(result);
                break;
            case 4:
                result = calc->tangent(value);
                operation = "tan(" + std::to_string(value) + ") = " + std::to_string(result);
                break;
            case 5:
                result = calc->logarithm(value);
                operation = "log(" + std::to_string(value) + ") = " + std::to_string(result);
                break;
            case 6:
                result = calc->naturalLog(value);
                operation = "ln(" + std::to_string(value) + ") = " + std::to_string(result);
                break;
            case 7:
                result = calc->factorial(static_cast<int>(value));
                operation = std::to_string(static_cast<int>(value)) + "! = " + std::to_string(result);
                break;
        }

        calc->addToHistory(operation);
        std::cout << "\nResult: " << std::fixed << std::setprecision(10) << result << "\n";

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    waitForEnter();
}

void UIHandler::handleExpressionEvaluation() {
    std::cout << "\nExpression Evaluation\n";
    std::cout << "Supported functions: sin, cos, tan, sqrt, log, ln, fact\n";
    std::cout << "Supported operators: +, -, *, /, ^\n";
    std::cout << "Example: 2 + 3 * sin(45) + sqrt(16)\n\n";

    std::string expression;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expression);

    if (expression.empty()) {
        std::cout << "Empty expression!\n";
        waitForEnter();
        return;
    }

    try {
        double result = calc->evaluateExpression(expression);
        std::string operation = expression + " = " + std::to_string(result);
        calc->addToHistory(operation);

        std::cout << "\nResult: " << std::fixed << std::setprecision(10) << result << "\n";

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    waitForEnter();
}

void UIHandler::handleMemoryOperation() {
    std::cout << "\nMemory Operations\n";
    std::cout << "1. Store (MS)\n2. Recall (MR)\n3. Clear (MC)\n";
    std::cout << "4. Add (M+)\n5. Subtract (M-)\n";
    std::cout << "Enter operation (1-5): ";

    int op;
    if (!(std::cin >> op) || op < 1 || op > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid operation\n";
        waitForEnter();
        return;
    }

    switch (op) {
        case 1: {
            double value;
            std::cout << "Enter value to store: ";
            if (std::cin >> value) {
                calc->memoryStore(value);
                std::cout << "Value stored in memory!\n";
            } else {
                std::cout << "Invalid number\n";
            }
            break;
        }
        case 2:
            std::cout << "Memory value: " << std::fixed << std::setprecision(10)
                    << calc->memoryRecall() << "\n";
            break;
        case 3:
            calc->memoryClear();
            std::cout << "Memory cleared\n";
            break;
        case 4: {
            double value;
            std::cout << "Enter value to add: ";
            if (std::cin >> value) {
                calc->memoryAdd(value);
                std::cout << "Value added to memory\n";
            } else {
                std::cout << "Invalid number\n";
            }
            break;
        }
        case 5: {
            double value;
            std::cout << "Enter value to subtract: ";
            if (std::cin >> value) {
                calc->memorySubtract(value);
                std::cout << "Value subtracted from memory\n";
            } else {
                std::cout << "Invalid number\n";
            }
            break;
        }
    }

    waitForEnter();
}

void UIHandler::displayHistory() {
    std::cout << "\nCalculation History\n";
    printSeparator();

    auto history = calc->getHistory();
    if (history.empty()) {
        std::cout << "No calculations in history.\n";
    } else {
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << std::setw(3) << (i + 1) << ". " << history[i] << "\n";
        }
    }

    std::cout << "\n1. Clear history\n2. Back to main menu\n";
    std::cout << "Enter choice: ";

    int choice;
    if (std::cin >> choice && choice == 1) {
        calc->clearHistory();
        std::cout << "History cleared.\n";
    }

    waitForEnter();
}

void UIHandler::handleSettings() {
    std::cout << "\nSettings\n";
    std::cout << "1. Toggle Angle Mode (Current: "
              << (calc->getAngleMode() ? "Radians" : "Degrees") << ")\n";
    std::cout << "2. Back to main menu\n";
    std::cout << "Enter choice: ";

    int choice;
    if (std::cin >> choice && choice == 1) {
        calc->setAngleMode(!calc->getAngleMode());
        std::cout << "Angle mode changed to: "
                  << (calc->getAngleMode() ? "Radians" : "Degrees") << "\n";
    }

    waitForEnter();
}

void UIHandler::printSeparator() {
    std::cout << "===============================================\n";
}

void UIHandler::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void UIHandler::setCalculator(Calculator* calculator) {
    calc = calculator;
}