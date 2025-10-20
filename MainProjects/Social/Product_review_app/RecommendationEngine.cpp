#include "RecommendationEngine.h"
#include "Utils.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

RecommendationEngine::RecommendationEngine(Database* db) : database(db) {}

std::vector<RecommendationScore> RecommendationEngine::getRecommendations(int userId, int count) {
    return getHybridRecommendations(userId, count);
}

std::vector<RecommendationScore> RecommendationEngine::getContentBasedRecommendations(
    int userId, int count) {
    User* user = database->getUser(userId);
    if (!user) return std::vector<RecommendationScore>();
    
    std::vector<Product> allProducts = database->getAllProducts();
    std::vector<RecommendationScore> scores;
    
    std::vector<int> purchaseHistory = user->getPurchaseHistory();
    std::map<std::string, int> categoryPrefs = user->getCategoryPreferences();
    
    for (const auto& product : allProducts) {
        if (user->hasPurchased(product.getId())) continue;
        if (!product.getIsActive()) continue;
        
        double score = 0.0;
        std::string reason = "";
        
        std::string category = product.getCategory();
        if (categoryPrefs.find(category) != categoryPrefs.end()) {
            score += categoryPrefs[category] * 10.0;
            reason = "Based on your interest in " + category;
        }
        
        score += product.getAverageRating() * 5.0;
        
        for (int purchasedId : purchaseHistory) {
            Product* purchased = database->getProduct(purchasedId);
            if (purchased) {
                double similarity = calculateProductSimilarity(*purchased, product);
                if (similarity > 0.5) {
                    score += similarity * 15.0;
                    if (reason.empty()) {
                        reason = "Similar to products you've purchased";
                    }
                }
            }
        }
        
        if (score > 0) {
            if (reason.empty()) reason = "Popular in your preferred categories";
            scores.push_back(RecommendationScore(product.getId(), score, reason));
        }
    }
    
    std::sort(scores.begin(), scores.end(), 
              [](const RecommendationScore& a, const RecommendationScore& b) {
                  return a.score > b.score;
              });
    
    if (scores.size() > static_cast<size_t>(count)) {
        scores.resize(count);
    }
    
    return scores;
}

std::vector<RecommendationScore> RecommendationEngine::getTopRatedProducts(int count) {
    std::vector<Product> allProducts = database->getAllProducts();
    std::vector<RecommendationScore> scores;
    
    for (const auto& product : allProducts) {
        if (!product.getIsActive()) continue;
        if (product.getTotalReviews() < 3) continue;
        
        double score = product.getAverageRating() * product.getTotalReviews();
        scores.push_back(RecommendationScore(
            product.getId(), score, 
            "Highly rated with " + std::to_string(product.getTotalReviews()) + " reviews"));
    }
    
    std::sort(scores.begin(), scores.end(), 
              [](const RecommendationScore& a, const RecommendationScore& b) {
                  return a.score > b.score;
              });
    
    if (scores.size() > static_cast<size_t>(count)) {
        scores.resize(count);
    }
    
    return scores;
}

std::vector<RecommendationScore> RecommendationEngine::getCategoryRecommendations(
    const std::string& category, int count) {
    std::vector<Product> categoryProducts = database->getProductsByCategory(category);
    std::vector<RecommendationScore> scores;
    
    for (const auto& product : categoryProducts) {
        if (!product.getIsActive()) continue;
        
        double score = product.getAverageRating() * 10.0;
        if (product.getTotalReviews() > 5) {
            score += product.getTotalReviews() * 2.0;
        }
        
        scores.push_back(RecommendationScore(
            product.getId(), score, "Top rated in " + category));
    }
    
    std::sort(scores.begin(), scores.end(), 
              [](const RecommendationScore& a, const RecommendationScore& b) {
                  return a.score > b.score;
              });
    
    if (scores.size() > static_cast<size_t>(count)) {
        scores.resize(count);
    }
    
    return scores;
}

void RecommendationEngine::clearCache() {
    userSimilarityCache.clear();
    collaborativeCache.clear();
}

void RecommendationEngine::rebuildCache() {
    clearCache();
    std::vector<User> allUsers = database->getAllUsers();
    
    for (size_t i = 0; i < allUsers.size(); i++) {
        for (size_t j = i + 1; j < allUsers.size(); j++) {
            double similarity = calculateUserSimilarity(allUsers[i], allUsers[j]);
            userSimilarityCache[allUsers[i].getId()][allUsers[j].getId()] = similarity;
            userSimilarityCache[allUsers[j].getId()][allUsers[i].getId()] = similarity;
        }
    }
}