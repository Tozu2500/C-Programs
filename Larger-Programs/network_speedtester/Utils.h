#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>

namespace Utils {
    // String utilities
    std::string trim(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string toLower(const std::string& str);

    // Network utilities
    std::string generateRandomData(size_t size);
    std::string extractHostname(const std::string& url);
    bool isValidUrl(const std::string& url);

    // Time utilities
    std::chrono::milliseconds getCurrentTime();
    double getElapsedSeconds(const std::chrono::milliseconds& start);

    // Formatting utilities
    std::string formatBytes(size_t bytes);
    std::string formatDuration(double seconds);
    std::string formatPercentage(double value);

    // System utilities
    void clearScreen();
    void printHeader(const std::string& title);
    void printSeparator();

    // Color output, if the terminal supports it
    enum class Color {
        Reset,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan
    };

    std::string colorize(const std::string& text, Color color);
}

#endif // UTILS_H