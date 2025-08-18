#include "TerminalUI.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

TerminalUI::TerminalUI() : running(false), dataLoaded(false) {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    initializeConsole();
}

TerminalUI::~TerminalUI() {
    restoreConsole();
}

void TerminalUI::initializeConsole() {
    GetConsoleScreenBufferInfo(hConsole, &originalConsoleInfo);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    consoleWidth = getConsoleWidth();
    consoleHeight = getConsoleHeight();
}

void TerminalUI::restoreConsole() {
    SetConsoleTextAttribute(hConsole, originalConsoleInfo.wAttributes);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void TerminalUI::run() {
    running = true;
    clearScreen();

    while (running) {
        refreshDisplay();
        handleInput();
    }
}

void TerminalUI::displayFileList(const FileInfo& rootInfo) {
    rootData = rootInfo;
    dataLoaded = true;

    currentState.items.clear();
    currentState.items.push_back(rootInfo);
    for (const auto& child : rootInfo.getChildren()) {
        currentState.items.push_back(child);
    }

    currentState.selectedIndex = 0;
    currentState.scrollOffset = 0;
    currentState.currentPath = rootInfo.getName();
}

void TerminalUI::handleInput() {
    if (!_kbhit()) {
        Sleep(50);
        return;
    }

    int key = _getch();

    switch (key) {
        case 224:
            key = _getch(); // Handle arrow keys
            switch (key) {
                case 72: // Up arrow
                    navigateUp();
                    break;
                case 80: // Down arrow
                    navigateDown();
                    break;
            }
            break;
        case 13:
            navigateEnter();
            break;
        case 8:
        case 27:
            navigateBack();
            break;
        case 'q':
        case 'Q':
            running = false;
            break;
        case 'h':
        case 'H':
            showHelp();
            break;
        case 'a':
        case 'A':
            showAbout();
            break;
        case 'r':
        case 'R':
            if (dataLoaded) {
                currentState.selectedIndex = 0;
                currentState.scrollOffset = 0;
            }
            break;
    }
}

void TerminalUI::navigateUp() {
    if (!dataLoaded || currentState.items.empty()) return;

    if (currentState.selectedIndex > 0) {
        currentState.selectedIndex--;

        if (currentState.selectedIndex < currentState.scrollOffset) {
            currentState.scrollOffset = currentState.selectedIndex;
        }
    }
}

void TerminalUI::navigateDown() {
    if (!dataLoaded || currentState.items.empty()) return;

    if (currentState.selectedIndex < static_cast<int>(currentState.items.size()) - 1) {
        currentState.selectedIndex++;

        int maxVisible = consoleHeight - 6;
        if (currentState.selectedIndex >= currentState.scrollOffset + maxVisible) {
            currentState.scrollOffset = currentState.selectedIndex - maxVisible + 1;
        }
    }
}

void TerminalUI::navigateEnter() {
    if (!dataLoaded || currentState.items.empty()) return;

    const FileInfo& selectedItem = currentState.items[currentState.selectedIndex];

    if (selectedItem.isDirectory() && !selectedItem.getChildren().empty()) {
        navigationStack.push(currentState);

        NavigationState newState;
        newState.items.clear();
        newState.items.push_back(selectedItem);

        for (const auto& child : selectedItem.getChildren()) {
            newState.items.push_back(child);
        }

        newState.selectedIndex = 0;
        newState.scrollOffset = 0;
        newState.currentPath = currentState.currentPath + "\\" + selectedItem.getName();

        currentState = newState;
    }
}

void TerminalUI::navigateBack() {
    if (!navigationStack.empty()) {
        currentState = navigationStack.top();
        navigationStack.pop();
    } else if (dataLoaded) {
        running = false; // Exit if no more navigation states
    }
}

void TerminalUI::refreshDisplay() {
    if (!dataLoaded) {
        displayProgressDialog("No data loaded. Scan a directory first.");
        return;
    }

    displayHeader();
    displayItems();
    displayStatusBar();
}

void TerminalUI::displayHeader() {
    setConsoleColor(COLOR_HEADER);
    gotoxy(0, 0);

    std::string title = "Disk Usage Analyzer - " + currentState.currentPath;
    std::cout << std::setfill(' ') << std::left << std::setw(consoleWidth) << title;

    gotoxy(0, 1);
    std::cout << std::setfill('-') << std::setw(consoleWidth) << "";
}

void TerminalUI::displayItems() {
    int startY = 2;
    int maxVisible = consoleHeight - 6;
    int endIndex = std::min(currentState.scrollOffset + maxVisible, static_cast<int>(currentState.items.size()));

    for (int i = currentState.scrollOffset; i < endIndex; i++) {
        int y = startY + (i - currentState.scrollOffset);
        gotoxy(0, y);

        bool isSelected = (i == currentState.selectedIndex);
        const FileInfo& item = currentState.items[i];

        if (isSelected) {
            setConsoleColor(COLOR_HIGHLIGHT);
        } else if (item.isDirectory()) {
            setConsoleColor(COLOR_DIRECTORY);
        } else {
            setConsoleColor(COLOR_FILE);
        }

        std::string name = item.getName();
        if (item.isDirectory() && i > 0) {
            name = "[" + name + "]";
        }

        std::string sizeStr = item.getFormattedSize();
        double percentage = 0.0;

        if (i > 0 && !currentState.items.empty()) {
            percentage = item.getPercentage(currentState.items[0].getSize());
        }

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << percentage << "%";
        std::string percentStr = ss.str();

        int nameWidth = consoleWidth - 20 - 8;
        std::string displayName = truncateString(name, nameWidth);

        std::cout << std::setfill(' ')
        << std::left << std::setw(nameWidth) << displayName
        << std::right << std::setw(12) << sizeStr
        << std::right << std::setw(8) << percentStr;

        if (isSelected && consoleWidth > 50) {
            int barStart = nameWidth + 20;
            int barWidth = consoleWidth - barStart - 2;
            if (barWidth > 0) {
                drawProgressBar(barStart, y, barWidth, percentage / 100.0);
            }
        }

        std::cout << std::setfill(' ') << std::setw(consoleWidth - (nameWidth + 20)) << "";
    }

    for (int y = startY + (endIndex - currentState.scrollOffset); y < consoleHeight - 4; y++) {
        gotoxy(0, y);
        setConsoleColor(COLOR_DEFAULT);
        std::cout << std::setfill(' ') << std::setw(consoleWidth) << "";
    }
}

void TerminalUI::displayStatusBar() {
    int statusY = consoleHeight - 3;
    setConsoleColor(COLOR_STATUS);

    gotoxy(0, statusY);
    std::cout << std::setfill('-') << std::setw(consoleWidth) << "";
    
    gotoxy(0, statusY + 1);
    std::string statusText = "Items: " + std::to_string(currentState.items.size());
    if (!currentState.items.empty()) {
        statusText += " | Total: " + currentState.items[0].getFormattedSize();
    }
    std::cout << std::setfill(' ') << std::left << std::setw(consoleWidth) << statusText;

    gotoxy(0, statusY + 2);
    std::string helpText = "Up and Down arrows to navigate, Enter to open, ESC to quit, Q:Quit, H:Help, A:About, R:Reset";
    std::cout << std::setfill(' ') << std::left << std::setw(consoleWidth) << truncateString(helpText, consoleWidth);
}

void TerminalUI::showProgressBar(const std::string& currentFile, int filesProcessed) {
    clearScreen();
    displayProgressDialog("Scanning: " + truncateString(currentFile, consoleWidth - 20) +
    "\nFiles processed: " + std::to_string(filesProcessed) +
    "\nPress ESC to cancel");
}

void TerminalUI::displayProgressDialog(const std::string& message) {
    int dialogWidth = std::min(60, consoleWidth - 4);
    int dialogHeight = 8;
    int startX = (consoleWidth - dialogWidth) / 2;
    int startY = (consoleHeight - dialogHeight) / 2;

    setConsoleColor(COLOR_PROGRESS);

    for (int y = 0; y < dialogHeight; y++) {
        gotoxy(startX, startY + y);
        if (y == 0 || y == dialogHeight - 1) {
            std::cout << std::setfill('=') << std::setw(dialogWidth) << "";
        } else {
            std::cout << "=";
            std::cout << std::setfill(' ') << std::setw(dialogWidth - 2) << "";
            std::cout << "=";
        }
    }

    std::vector<std::string> lines;
    std::stringstream ss(message);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    int textStartY = startY + 2;
    for (size_t i = 0; i < lines.size() && i < 4; i++) {
        gotoxy(startX + 2, textStartY + i);
        std::string displayLine = truncateString(lines[i], dialogWidth - 4);
        std::cout << std::setfill(' ') << std::left << std::setw(dialogWidth - 4) << displayLine;
    }
}

void TerminalUI::showHelp() {
    clearScreen();
    setConsoleColor(COLOR_DEFAULT);

    std::cout << "DISK USAGE ANALYZER - Help\n";
    std::cout << "===============================\n\n";
    std::cout << "Navigation:\n";
    std::cout << "  - Use arrow keys to navigate up and down\n";
    std::cout << "  - Press Enter to open a selected directory\n";
    std::cout << "  - ESC/Backspace to go back\n";
    std::cout << "  R  - Reset to root directory\n";
    std::cout << "Commands:\n";
    std::cout << "  Q    - Quit the application\n";
    std::cout << "  H    - Show this help screen\n";
    std::cout << "  A    - Show information about this application\n";
    std::cout << "Display:\n";
    std::cout << "  - Directories are shown in brackets []\n";
    std::cout << "  - Files and directories are sorted by size, with largest being the first\n";
    std::cout << "  - Size is shown in appropriate units, e.g., KB, MB, GB\n";
    std::cout << "  - Percentage shows relative size within current directory\n\n";
    std::cout << "Press any key to continue...";

    _getch(); // Wait for user input
}

void TerminalUI::showAbout() {
    clearScreen();
    setConsoleColor(COLOR_DEFAULT);

    std::cout << "Disk Usage Analyzer\n";
    std::cout << "===============================\n\n";
     std::cout << "Version: 1.0\n";
    std::cout << "Platform: Windows\n\n";
    std::cout << "Description:\n";
    std::cout << "A terminal-based disk usage analyzer that helps you identify\n";
    std::cout << "which files and directories are consuming the most disk space.\n\n";
    std::cout << "Features:\n";
    std::cout << "- Recursive directory scanning\n";
    std::cout << "- Interactive navigation\n";
    std::cout << "- Size formatting and percentage display\n";
    std::cout << "- Progress indication during scanning\n";
    std::cout << "- Automatic sorting by size\n\n";
    std::cout << "Press any key to continue...";
    
    _getch();
}

void TerminalUI::clearScreen() {
    system("cls");
}

void TerminalUI::setConsoleColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void TerminalUI::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

int TerminalUI::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int TerminalUI::getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

std::string TerminalUI::truncateString(const std::string& str, int maxLength) {
     if (str.length() <= static_cast<size_t>(maxLength)) {
        return str;
    }

    if (maxLength <= 3) {
        return str.substr(0, maxLength);
    }

    return str.substr(0, maxLength - 3) + "...";
}

void TerminalUI::drawProgressBar(int x, int y, int width, double percentage) {
    if (width <= 2) return;
    
    gotoxy(x, y);
    std::cout << "[";
    
    int fillWidth = static_cast<int>((width - 2) * percentage);
    for (int i = 0; i < width - 2; i++) {
        if (i < fillWidth) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    
    std::cout << "]";
}