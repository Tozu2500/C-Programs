#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Database.h"
#include "RecommendationEngine.h"
#include "Analytics.h"
#include <string>

class UserInterface {
private:
    Database* database;
    RecommendationEngine* recommendationEngine;
    Analytics* analytics;
    User* currentUser;
    bool isRunning;
    
    void clearScreen();
    void pauseScreen();
    std::string getInput(const std::string& prompt);
    int getIntInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    bool getYesNoInput(const std::string& prompt);
    
    void displayHeader(const std::string& title);
    void displayMenu(const std::vector<std::string>& options);
    void displayProduct(const Product& product);
    void displayReview(const Review& review);
    void displayRecommendation(const RecommendationScore& rec);
    void displayProductList(const std::vector<Product>& products);
    
    void showMainMenu();
    void showUserMenu();
    void showAdminMenu();
    void showProductMenu();
    void showReviewMenu();
    void showRecommendationMenu();
    void showAnalyticsMenu();
    
    void handleLogin();
    void handleRegistration();
    void handleLogout();
    
    void handleBrowseProducts();
    void handleSearchProducts();
    void handleViewProduct();
    void handleAddProduct();
    void handleEditProduct();
    void handleDeleteProduct();
    
    void handleViewReviews();
    void handleAddReview();
    void handleEditReview();
    void handleDeleteReview();
    void handleMarkReviewHelpful();
    
    void handleGetRecommendations();
    void handleViewSimilarProducts();
    void handleViewTrendingProducts();
    void handleViewTopRated();
    void handleCategoryRecommendations();
    
    void handleProductAnalytics();
    void handleCategoryAnalytics();
    void handleUserAnalytics();
    void handleSystemReport();
    
    void handleManageWishlist();
    void handleViewPurchaseHistory();
    void handleUserProfile();
    
public:
    UserInterface(Database* db, RecommendationEngine* recEngine, Analytics* analyticsEngine);
    ~UserInterface();
    
    void run();
    void setCurrentUser(User* user);
    User* getCurrentUser();
};

#endif