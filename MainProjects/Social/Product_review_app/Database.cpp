#include "Database.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Database::Database() : nextProductId(1), nextReviewId(1), nextUserId(1), 
                       dataDirectory("data/") {}

Database::Database(const std::string& directory) 
    : nextProductId(1), nextReviewId(1), nextUserId(1), dataDirectory(directory) {}

bool Database::loadFromFiles() {
    std::string productsFile = dataDirectory + "products.txt";
    std::string reviewsFile = dataDirectory + "reviews.txt";
    std::string usersFile = dataDirectory + "users.txt";
    
    std::ifstream pFile(productsFile);
    if (pFile.is_open()) {
        std::string line;
        while (std::getline(pFile, line)) {
            if (!line.empty()) {
                Product product;
                parseProductLine(line, product);
                products.push_back(product);
                if (product.getId() >= nextProductId) {
                    nextProductId = product.getId() + 1;
                }
            }
        }
        pFile.close();
    }
    
    std::ifstream rFile(reviewsFile);
    if (rFile.is_open()) {
        std::string line;
        while (std::getline(rFile, line)) {
            if (!line.empty()) {
                Review review;
                parseReviewLine(line, review);
                reviews.push_back(review);
                if (review.getId() >= nextReviewId) {
                    nextReviewId = review.getId() + 1;
                }
            }
        }
        rFile.close();
    }
    
    std::ifstream uFile(usersFile);
    if (uFile.is_open()) {
        std::string line;
        while (std::getline(uFile, line)) {
            if (!line.empty()) {
                User user;
                parseUserLine(line, user);
                users.push_back(user);
                if (user.getId() >= nextUserId) {
                    nextUserId = user.getId() + 1;
                }
            }
        }
        uFile.close();
    }
    
    calculateProductRatings();
    return true;
}

bool Database::saveToFiles() {
    std::string productsFile = dataDirectory + "products.txt";
    std::string reviewsFile = dataDirectory + "reviews.txt";
    std::string usersFile = dataDirectory + "users.txt";
    
    std::ofstream pFile(productsFile);
    if (pFile.is_open()) {
        for (const auto& product : products) {
            pFile << product.toFileString() << "\n";
        }
        pFile.close();
    } else {
        return false;
    }
    
    std::ofstream rFile(reviewsFile);
    if (rFile.is_open()) {
        for (const auto& review : reviews) {
            rFile << review.toFileString() << "\n";
        }
        rFile.close();
    } else {
        return false;
    }
    
    std::ofstream uFile(usersFile);
    if (uFile.is_open()) {
        for (const auto& user : users) {
            uFile << user.toFileString() << "\n";
        }
        uFile.close();
    } else {
        return false;
    }
    
    return true;
}

bool Database::addProduct(const Product& product) {
    products.push_back(product);
    return true;
}

bool Database::addReview(const Review& review) {
    reviews.push_back(review);
    Product* product = getProduct(review.getProductId());
    if (product) {
        product->updateRating(review.getRating());
    }
    return true;
}

bool Database::addUser(const User& user) {
    users.push_back(user);
    return true;
}

bool Database::updateProduct(const Product& product) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getId() == product.getId()) {
            products[i] = product;
            return true;
        }
    }
    return false;
}

bool Database::updateReview(const Review& review) {
    for (size_t i = 0; i < reviews.size(); i++) {
        if (reviews[i].getId() == review.getId()) {
            reviews[i] = review;
            return true;
        }
    }
    return false;
}

bool Database::updateUser(const User& user) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getId() == user.getId()) {
            users[i] = user;
            return true;
        }
    }
    return false;
}

bool Database::deleteProduct(int productId) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == productId) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

bool Database::deleteReview(int reviewId) {
    for (auto it = reviews.begin(); it != reviews.end(); ++it) {
        if (it->getId() == reviewId) {
            reviews.erase(it);
            return true;
        }
    }
    return false;
}

bool Database::deleteUser(int userId) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getId() == userId) {
            users.erase(it);
            return true;
        }
    }
    return false;
}

Product* Database::getProduct(int productId) {
    for (auto& product : products) {
        if (product.getId() == productId) {
            return &product;
        }
    }
    return nullptr;
}

Review* Database::getReview(int reviewId) {
    for (auto& review : reviews) {
        if (review.getId() == reviewId) {
            return &review;
        }
    }
    return nullptr;
}

User* Database::getUser(int userId) {
    for (auto& user : users) {
        if (user.getId() == userId) {
            return &user;
        }
    }
    return nullptr;
}

User* Database::getUserByUsername(const std::string& username) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

std::vector<Product> Database::getAllProducts() {
    return products;
}

std::vector<Review> Database::getAllReviews() {
    return reviews;
}

std::vector<User> Database::getAllUsers() {
    return users;
}

std::vector<Review> Database::getReviewsForProduct(int productId) {
    std::vector<Review> result;
    for (const auto& review : reviews) {
        if (review.getProductId() == productId) {
            result.push_back(review);
        }
    }
    return result;
}

std::vector<Product> Database::getProductsByCategory(const std::string& category) {
    std::vector<Product> result;
    for (const auto& product : products) {
        if (product.getCategory() == category) {
            result.push_back(product);
        }
    }
    return result;
}

std::vector<Product> Database::searchProducts(const std::string& query) {
    std::vector<Product> result;
    for (const auto& product : products) {
        if (product.matchesSearch(query)) {
            result.push_back(product);
        }
    }
    return result;
}

int Database::getNextProductId() {
    return nextProductId++;
}

int Database::getNextReviewId() {
    return nextReviewId++;
}

int Database::getNextUserId() {
    return nextUserId++;
}

void Database::calculateProductRatings() {
    for (auto& product : products) {
        std::vector<Review> productReviews = getReviewsForProduct(product.getId());
        if (!productReviews.empty()) {
            double sum = 0.0;
            for (const auto& review : productReviews) {
                sum += review.getRating();
            }
            product.setAverageRating(sum / productReviews.size());
            product.setTotalReviews(productReviews.size());
        }
    }
}

std::map<std::string, int> Database::getCategoryDistribution() {
    std::map<std::string, int> distribution;
    for (const auto& product : products) {
        distribution[product.getCategory()]++;
    }
    return distribution;
}

double Database::getAverageRatingForCategory(const std::string& category) {
    std::vector<Product> categoryProducts = getProductsByCategory(category);
    if (categoryProducts.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& product : categoryProducts) {
        sum += product.getAverageRating();
    }
    return sum / categoryProducts.size();
}

void Database::parseProductLine(const std::string& line, Product& product) {
    std::vector<std::string> parts = splitString(line, '|');
    if (parts.size() >= 12) {
        product.setId(std::stoi(parts[0]));
        product.setName(parts[1]);
        product.setCategory(parts[2]);
        product.setDescription(parts[3]);
        product.setBasePrice(std::stod(parts[4]));
        product.setStockQuantity(std::stoi(parts[5]));
        product.setAverageRating(std::stod(parts[6]));
        product.setTotalReviews(std::stoi(parts[7]));
        product.setManufacturer(parts[8]);
        product.setYearReleased(std::stoi(parts[9]));
        product.setIsActive(std::stoi(parts[10]) == 1);
        
        if (!parts[11].empty()) {
            std::vector<std::string> tags = splitString(parts[11], ',');
            for (const auto& tag : tags) {
                product.addTag(trim(tag));
            }
        }
    }
}

void Database::parseReviewLine(const std::string& line, Review& review) {
    std::vector<std::string> parts = splitString(line, '|');
    if (parts.size() >= 13) {
        review.setId(std::stoi(parts[0]));
        review.setProductId(std::stoi(parts[1]));
        review.setUserId(std::stoi(parts[2]));
        review.setUserName(parts[3]);
        review.setRating(std::stod(parts[4]));
        review.setTitle(parts[5]);
        review.setContent(parts[6]);
        review.setTimestamp(std::stoll(parts[7]));
        review.setHelpfulCount(std::stoi(parts[8]));
        review.setNotHelpfulCount(std::stoi(parts[9]));
        review.setVerified(std::stoi(parts[10]) == 1);
        review.setReviewerLocation(parts[11]);
    }
}

void Database::parseUserLine(const std::string& line, User& user) {
    std::vector<std::string> parts = splitString(line, '|');
    if (parts.size() >= 13) {
        user.setId(std::stoi(parts[0]));
        user.setUsername(parts[1]);
        user.setEmail(parts[2]);
        user.setPassword(parts[3]);
        user.setFullName(parts[4]);
        user.setRegistrationDate(std::stoll(parts[5]));
        user.setTrustScore(std::stoi(parts[6]));
        user.setIsPremium(std::stoi(parts[7]) == 1);
        user.setLocation(parts[8]);
        
        if (!parts[9].empty()) {
            std::vector<std::string> reviewed = splitString(parts[9], ',');
            for (const auto& id : reviewed) {
                if (!id.empty()) user.addReviewedProduct(std::stoi(id));
            }
        }
        
        if (!parts[10].empty()) {
            std::vector<std::string> purchases = splitString(parts[10], ',');
            for (const auto& id : purchases) {
                if (!id.empty()) user.addPurchase(std::stoi(id));
            }
        }
        
        if (!parts[11].empty()) {
            std::vector<std::string> wishlistItems = splitString(parts[11], ',');
            for (const auto& id : wishlistItems) {
                if (!id.empty()) user.addToWishlist(std::stoi(id));
            }
        }
        
        if (!parts[12].empty()) {
            std::vector<std::string> prefs = splitString(parts[12], ',');
            for (const auto& pref : prefs) {
                std::vector<std::string> keyVal = splitString(pref, ':');
                if (keyVal.size() == 2) {
                    for (int i = 0; i < std::stoi(keyVal[1]); i++) {
                        user.incrementCategoryPreference(keyVal[0]);
                    }
                }
            }
        }
    }
}

std::vector<std::string> Database::splitString(const std::string& str, char delimiter) {
    return Utils::split(str, delimiter);
}

std::string Database::trim(const std::string& str) {
    return Utils::trim(str);
}