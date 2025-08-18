#include "Application.h"
#include <iostream>
#include <windows.h>

void setupConsole() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    if (csbi.dwSize.X < 120 || csbi.dwSize.Y < 30) {
        COORD newSize;
        newSize.X = 120;
        newSize.Y = 50;
        SetConsoleScreenBufferSize(hOut, newSize);

        SMALL_RECT windowSize;
        windowSize.Left = 0;
        windowSize.Top = 0;
        windowSize.Right = 119;
        windowSize.Bottom = 29;
        SetConsoleWindowInfo(hOut, TRUE, &windowSize);
    }
}

int main(int argc, char* argv[]) {
    try {
        setupConsole();

        Application app;
        return app.run(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        std::cerr << "Press any key to exit...";
        std::cin.get();
        return 1;
    } catch (...) {
        std::cerr << "Unknown fatal error occurred." << std::endl;
        std::cerr << "Press any key to exit...";
        std::cin.get();
        return 1;
    }
}