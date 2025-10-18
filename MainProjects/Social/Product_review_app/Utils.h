#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    static std::string toLowerCase(const std::string& str);
    static std::string toUpperCase(const std::string& str);
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter);
    
    static bool isValidEmail(const std::string& email);
    static bool isValidRating(double rating);
    static std::string encodePassword(const std::string& password);
    static bool verifyPassword(const std::string& password, const std::string& encoded);
    
    static std::string getCurrentTimeString();
    static std::string formatTimestamp(time_t timestamp);
    static time_t parseTimestamp(const std::string& timeStr);
    
    static double calculateCosineSimilarity(const std::vector<double>& v1, 
                                            const std::vector<double>& v2);
    static double calculateEuclideanDistance(const std::vector<double>& v1, 
                                             const std::vector<double>& v2);
    
    static std::string formatCurrency(double amount);
    static std::string formatPercentage(double value);
    static std::string truncateString(const std::string& str, int maxLength);
    
    static bool fileExists(const std::string& filename);
    static std::string readFile(const std::string& filename);
    static bool writeFile(const std::string& filename, const std::string& content);
    
    static int randomInt(int min, int max);
    static double randomDouble(double min, double max);
    static std::string generateId(int length);
};

#endif