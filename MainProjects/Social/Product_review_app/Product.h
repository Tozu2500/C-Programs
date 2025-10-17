#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    std::string description;
    double basePrice;
    int stockQuantity;
    std::vector<std::string> tags;
    double averageRating;
    int totalReviews;
    std::string manufacturer;
    int yearReleased;
    bool isActive;

public:
    Product();
    Product(int id, const std::string& name, const std::string& category,
            const std::string& description, double price, int stock);

    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    double getBasePrice() const;
    int getStockQuantity() const;
    std::vector<std::string> getTags() const;
    double getAverageRating() const;
    int getTotalReviews() const;
    std::string getManufacturer() const;
    int getYearReleased() const;
    bool getIsActive() const;

    void setId(int id);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setDescription(const std::string& description);
    void setBasePrice(double price);
    void setStockQuantity(int stock);
    void addTag(const std::string& tag);
    void setAverageRating(double rating);
    void setTotalReviews(int reviews);
    void setManufacturer(const std::string& manufacturer);
    void setYearReleased(int year);
    void setIsActive(bool active);

    void updateRating(double newRating);
    std::string toString() const;
    std::string toFileString() const;
    bool matchesSearch(const std::string& query) const;
};

#endif  // Product_h
