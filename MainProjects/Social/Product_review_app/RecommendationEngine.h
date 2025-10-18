#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "Database.h"
#include "Product.h"
#include "User.h"
#include <vector>
#include <map>

struct RecommendationScore {
    int productId;
    double score;
    std::string reason;
    
    RecommendationScore(int id, double s, const std::string& r) 
        : productId(id), score(s), reason(r) {}
};

class RecommendationEngine {
private:
    Database* database;
    std::map<int, std::map<int, double>> userSimilarityCache;
    std::map<int, std::vector<int>> collaborativeCache;
    
    double calculateUserSimilarity(const User& user1, const User& user2);
    double calculateProductSimilarity(const Product& p1, const Product& p2);
    std::vector<int> findSimilarUsers(int userId, int topN);
    double calculateCategoryAffinity(const User& user, const std::string& category);
    double calculateRatingPrediction(int userId, int productId);
    bool hasCommonElements(const std::vector<std::string>& v1, 
                          const std::vector<std::string>& v2);
    
public:
    RecommendationEngine(Database* db);
    
    std::vector<RecommendationScore> getRecommendations(int userId, int count);
    std::vector<RecommendationScore> getContentBasedRecommendations(int userId, int count);
    std::vector<RecommendationScore> getCollaborativeRecommendations(int userId, int count);
    std::vector<RecommendationScore> getHybridRecommendations(int userId, int count);
    std::vector<RecommendationScore> getTrendingProducts(int count);
    std::vector<RecommendationScore> getSimilarProducts(int productId, int count);
    std::vector<RecommendationScore> getTopRatedProducts(int count);
    std::vector<RecommendationScore> getCategoryRecommendations(
        const std::string& category, int count);
    
    void clearCache();
    void rebuildCache();
    std::map<std::string, double> analyzeUserPreferences(int userId);
    double predictRating(int userId, int productId);
};

#endif