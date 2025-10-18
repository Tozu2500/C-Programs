#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include "Review.h"
#include "User.h"
#include <vector>
#include <string>
#include <map>

class Database {
private:
    std::vector<Product> products;
    std::vector<Review> reviews;
    std::vector<User> users;
    int nextProductId;
    int nextReviewId;
    int nextUserId;
    std::string dataDirectory;
    
    void parseProductLine(const std::string& line, Product& product);
    void parseReviewLine(const std::string& line, Review& review);
    void parseUserLine(const std::string& line, User& user);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    std::string trim(const std::string& str);

public:
    Database();
    Database(const std::string& directory);
    
    bool loadFromFiles();
    bool saveToFiles();
    
    bool addProduct(const Product& product);
    bool addReview(const Review& review);
    bool addUser(const User& user);
    
    bool updateProduct(const Product& product);
    bool updateReview(const Review& review);
    bool updateUser(const User& user);
    
    bool deleteProduct(int productId);
    bool deleteReview(int reviewId);
    bool deleteUser(int userId);
    
    Product* getProduct(int productId);
    Review* getReview(int reviewId);
    User* getUser(int userId);
    User* getUserByUsername(const std::string& username);
    
    std::vector<Product> getAllProducts();
    std::vector<Review> getAllReviews();
    std::vector<User> getAllUsers();
    
    std::vector<Review> getReviewsForProduct(int productId);
    std::vector<Product> getProductsByCategory(const std::string& category);
    std::vector<Product> searchProducts(const std::string& query);
    
    int getNextProductId();
    int getNextReviewId();
    int getNextUserId();
    
    void calculateProductRatings();
    std::map<std::string, int> getCategoryDistribution();
    double getAverageRatingForCategory(const std::string& category);
};

#endif