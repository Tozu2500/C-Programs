#include "../include/utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>

void clearScreen()
{
    system("cls");
}

void pauseForUser()
{
    std::cout << "\n Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::string trimWhitespace(const std::string& str)
{
    auto start = std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    });
    auto end = std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base();
    if (start >= end) return "";
    return std::string(start, end);
}

bool isValidKey(const std::string& key)
{
    if (key.empty()) return false;
    for (char ch : key)
        if (std::isspace(static_cast<unsigned char>(ch))) return false;
    return true;
}

int readInt(const std::string& prompt, int minVal, int maxVal)
{
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number between " << minVal << " and " << maxVal << ".\n";
    }
}

std::string readLine(const std::string& prompt)
{
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        line = trimWhitespace(line);
        if (!line.empty()) return line;
        std::cout << "Input cannot be empty.\n";
    }
}

std::string centerText(const std::string& text, int width)
{
    int len = static_cast<int>(text.length());
    if (len >= width) return text;
    return std::string((width - len) / 2, ' ') + text;
}

std::string repeatChar(char ch, int count)
{
    if (count <= 0) return "";
    return std::string(count, ch);
}