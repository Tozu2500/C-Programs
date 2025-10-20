#include "User.h"
#include "Utils.h"
#include <sstream>
#include <algorithm>
#include <ctime>

User::User() : id(0), username(""), email(""), password(""), fullName(""),
                registrationDate(0), trustScore(50), isPremium(false),
                location("") {}

User::User(int id, const std::string& username, const std::string& email,
            const std::string& password)
    : id(id), username(username), email(email), password(password),
        fullName(""), trustScore(50), isPremium(false), location("") {
    registrationDate = std::time(nullptr);
}

int User::getId() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getFullName() const {
    return fullName;
}

time_t User::getRegistrationDate() const {
    return registrationDate;
}

std::vector<int> User::getReviewedProducts() const {
    return reviewedProducts;
}

std::vector<int> User::getPurchaseHistory() const {
    return purchaseHistory;
}

std::vector<int> User::getWishlist() const {
    return wishlist;
}

std::map<std::string, int> User::getCategoryPreferences() const {
    return categoryPreferences;
}

int User::getTrustScore() const {
    return trustScore;
}

bool User::getIsPremium() const {
    return isPremium;
}

std::string User::getLocation() const {
    return location;
}

void User::setId(int id) {
    this->id = id;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setFullName(const std::string& fullName) {
    this->fullName = fullName;
}

void User::setRegistrationDate(time_t date) {
    this->registrationDate = date;
}

void User::setTrustScore(int score) {
    this->trustScore = score;
}

void User::setIsPremium(bool premium) {
    this->isPremium = premium;
}

void User::setLocation(const std::string& location) {
    this->location = location;
}

void User::addReviewedProduct(int productId) {
    if (!hasReviewed(productId)) {
        reviewedProducts.push_back(productId);
    }
}

void User::addToWishlist(int productId) {
    if (!isInWishlist(productId)) {
        wishlist.push_back(productId);
    }
}

void User::removeFromWishlist(int productId) {
    auto it = std::find(wishlist.begin(), wishlist.end(), productId);
    if (it != wishlist.end()) {
        wishlist.erase(it);
    }
}

void User::incrementCategoryPreference(const std::string& category) {
    categoryPreferences[category]++;
}

bool User::hasReviewed(int productId) const {
    return std::find(reviewedProducts.begin(), reviewedProducts.end(), productId)
        != reviewedProducts.end();
}

bool User::hasPurchased(int productId) const {
    return std::find(purchaseHistory.begin(), purchaseHistory.end(), productId)
        != purchaseHistory.end();
}

bool User::isInWishlist(int productId) const {
    return std::find(wishlist.begin(), wishlist.end(), productId)
        != wishlist.end();
}

std::string User::toString() const {
    std::stringstream ss;
    ss << "User ID: " << id << "\n";
    ss << "Username: " << username << "\n";
    ss << "Email: " << email << "\n";
    ss << "Full Name: " << fullName << "\n";
    ss << "Registration Date: " << Utils::formatTimestamp(registrationDate) << "\n";
    ss << "Trust Score: " << trustScore << "\n";
    ss << "Premium: " << (isPremium ? "Yes" : "No") << "\n";
    ss << "Location: " << location << "\n";
    ss << "Reviews Written: " << reviewedProducts.size() << "\n";
    ss << "Purchases: " << purchaseHistory.size() << "\n";
    ss << "Wishlist Items: " << wishlist.size() << "\n";
    return ss.str();
}

std::string User::toFileString() const {
    std::stringstream ss;
    ss << id << "|" << username << "|" << email << "|" << password << "|"
       << fullName << "|" << registrationDate << "|" << trustScore << "|"
       << (isPremium ? 1 : 0) << "|" << location << "|";
    
    for (size_t i = 0; i < reviewedProducts.size(); i++) {
        ss << reviewedProducts[i];
        if (i < reviewedProducts.size() - 1) ss << ",";
    }
    ss << "|";
    
    for (size_t i = 0; i < purchaseHistory.size(); i++) {
        ss << purchaseHistory[i];
        if (i < purchaseHistory.size() - 1) ss << ",";
    }
    ss << "|";
    
    for (size_t i = 0; i < wishlist.size(); i++) {
        ss << wishlist[i];
        if (i < wishlist.size() - 1) ss << ",";
    }
    ss << "|";
    
    bool first = true;
    for (const auto& pair : categoryPreferences) {
        if (!first) ss << ",";
        ss << pair.first << ":" << pair.second;
        first = false;
    }
    
    return ss.str();
}