#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "Database.h"
#include <string>
#include <vector>
#include <map>

struct ProductAnalytics {
    int productId;
    std::string productName;
    double averageRating;
    int totalReviews;
    double ratingStdDev;
    int positiveReviews;
    int negativeReviews;
    int neutralReviews;
    double sentimentScore;
    std::vector<std::string> topKeywords;
};

struct CategoryAnalytics {
    std::string category;
    int productCount;
    double averageRating;
    int totalReviews;
    double averagePrice;
    int totalSales;
};

struct UserAnalytics {
    int userId;
    std::string username;
    int totalReviews;
    double averageRatingGiven;
    int helpfulVotes;
    double trustScore;
    std::vector<std::string> favoriteCategories;
};

class Analytics {
private:
    Database* database;
    
    double calculateStandardDeviation(const std::vector<double>& values);
    std::vector<std::string> extractKeywords(const std::string& text);
    std::map<std::string, int> getWordFrequency(const std::vector<std::string>& words);
    double calculateSentimentScore(const std::string& text);
    
public:
    Analytics(Database* db);
    
    ProductAnalytics analyzeProduct(int productId);
    CategoryAnalytics analyzeCategory(const std::string& category);
    UserAnalytics analyzeUser(int userId);
    
    std::vector<ProductAnalytics> getTopRatedProducts(int count);
    std::vector<ProductAnalytics> getMostReviewedProducts(int count);
    std::vector<CategoryAnalytics> getCategoryStats();
    std::vector<UserAnalytics> getTopReviewers(int count);
    
    std::map<int, int> getRatingDistribution(int productId);
    std::map<std::string, double> getCategorySentiment();
    std::vector<std::string> getTrendingKeywords(int count);
    
    double calculateReviewQuality(int reviewId);
    std::string generateProductReport(int productId);
    std::string generateCategoryReport(const std::string& category);
    std::string generateSystemReport();
};

#endif