#include "calculator.h"
#include "ui_handler.h"
#include <iostream>
#include <exception>
#include <windows.h>

void setupConsole() {
    SetConsoleTitle("Advanced Terminal Calculator v1.0");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    COORD newSize;
    newSize.X = 80;
    newSize.Y = 25;
    SetConsoleScreenBufferSize(hConsole, newSize);

    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = 79;
    windowSize.Bottom = 24;
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() {
    try {
        setupConsole();

        Calculator calculator;
        UIHandler ui(&calculator);

        ui.run();

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    } catch (...) {
        std::cerr << "Unknown fatal error occurred!" << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    return 0;
}