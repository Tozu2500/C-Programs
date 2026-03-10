#ifndef UTILS_H
#define UTILS_H

#include <string>

void clearScreen();
void pauseForUser();
std::string trimWhitespace(const std::string& str);
bool isValidKey(const std::string& key);
int readInt(const std::string& prompt, int minVal, int maxVal);
std::string readLine(const std::string& prompt);
std::string centerText(const std::string& text, int width = 60);
std::string repeatChar(char ch, int count);

#endif // UTILS_H