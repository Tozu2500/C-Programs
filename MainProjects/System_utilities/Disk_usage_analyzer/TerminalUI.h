#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "FileInfo.h"
#include <vector>
#include <string>
#include <stack>
#include <windows.h>

struct NavigationState {
    std::vector<FileInfo> items;
    int selectedIndex;
    int scrollOffset;
    std::string currentPath;

    NavigationState() : selectedIndex(0), scrollOffset(0) {}
};

class TerminalUI {
public:
    TerminalUI();
    ~TerminalUI();

    void run();
    void displayFileList(const FileInfo& rootInfo);
    void showProgressBar(const std::string& currentFile, int filesProcessed);
    void clearScreen();
    void showHelp();
    void showAbout();

private:
    void initializeConsole();
    void restoreConsole();
    void handleInput();
    void navigateUp();
    void navigateDown();
    void navigateEnter();
    void navigateBack();
    void refreshDisplay();
    void displayStatusBar();
    void displayHeader();
    void displayItems();
    void displayProgressDialog(const std::string& message);
    void setConsoleColor(int color);
    void gotoxy(int x, int y);
    int getConsoleWidth();
    int getConsoleHeight();
    std::string truncateString(const std::string& str, int maxLength);
    void drawProgressBar(int x, int y, int width, double percentage);

    static const int COLOR_DEFAULT = 7;
    static const int COLOR_HIGHLIGHTED = 12;
    static const int COLOR_DIRECTORY = 14;
    static const int COLOR_FILE = 15;
    static const int COLOR_HEADER = 11;
    static const int COLOR_STATUS = 10;
    static const int COLOR_PROGRESS = 13;

    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO originalConsoleInfo;

    std::stack<NavigationState> navigationStack;
    NavigationState currentState;
    bool running;
    FileInfo rootData;
    int consoleWidth;
    int consoleHeight;
    bool dataLoaded;
};

#endif // TERMINALUI_H