#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <map>

class User {
private:
    int id;
    std::string username;
    std::string email;
    std::string password;
    std::string fullName;
    time_t registrationDate;
    std::vector<int> reviewedProducts;
    std::vector<int> purchaseHistory;
    std::vector<int> wishlist;
    std::map<std::string, int> categoryPreferences;
    int trustScore;
    bool isPremium;
    std::string location;

public:
    User();
    User(int id, const std::string& username, const std::string& email, 
         const std::string& password);
    
    int getId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPassword() const;
    std::string getFullName() const;
    time_t getRegistrationDate() const;
    std::vector<int> getReviewedProducts() const;
    std::vector<int> getPurchaseHistory() const;
    std::vector<int> getWishlist() const;
    std::map<std::string, int> getCategoryPreferences() const;
    int getTrustScore() const;
    bool getIsPremium() const;
    std::string getLocation() const;
    
    void setId(int id);
    void setUsername(const std::string& username);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    void setFullName(const std::string& fullName);
    void setRegistrationDate(time_t date);
    void setTrustScore(int score);
    void setIsPremium(bool premium);
    void setLocation(const std::string& location);
    
    void addReviewedProduct(int productId);
    void addPurchase(int productId);
    void addToWishlist(int productId);
    void removeFromWishlist(int productId);
    void incrementCategoryPreference(const std::string& category);
    bool hasReviewed(int productId) const;
    bool hasPurchased(int productId) const;
    bool isInWishlist(int productId) const;
    std::string toString() const;
    std::string toFileString() const;
};

#endif