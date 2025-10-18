#include "Product.h"
#include "Utils.h"
#include <sstream>
#include <algorithm>

Product::Product() : id(0), name(""), category(""), description(""),
                    basePrice(0.0), stockQuantity(0), averageRating(0.0),
                    totalReviews(0), manufacturer(""), yearReleased(0),
                    isActive(true) {}

Product::Product(int id, const std::string& name, const std::string& category,
                const std::string& description, double price, int stock)
        : id(id), name(name), category(category), description(description),
            basePrice(price), stockQuantity(stock), averageRating(0.0),
            totalReviews(0), manufacturer(""), yearReleased(0), isActive(true) {}


// Getters
int Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

std::string Product::getCategory() const {
    return category;
}

std::string Product::getDescription() const {
    return description;
}

double Product::getBasePrice() const {
    return basePrice;
}

int Product::getStockQuantity() const {
    return stockQuantity;
}

std::vector<std::string> Product::getTags() const {
    return tags;
}

double Product::getAverageRating() const {
    return averageRating;
}

int Product::getTotalReviews() const {
    return totalReviews;
}

std::string Product::getManufacturer() const {
    return manufacturer;
}

int Product::getYearReleased() const {
    return yearReleased;
}

bool Product::getIsActive() const {
    return isActive;
}

// Setters
void Product::setId(int id) {
    this->id = id;
}

void Product::setName(const std::string& name) {
    this->name = name;
}

void Product::setCategory(const std::string& category) {
    this->category = category;
}

void Product::setDescription(const std::string& description) {
    this->description = description;
}

void Product::setBasePrice(double price) {
    this->basePrice = price;
}

void Product::setStockQuantity(int stock) {
    this->stockQuantity = stock;
}

void Product::setAverageRating(double rating) {
    this->averageRating = rating;
}

void Product::setTotalReviews(int reviews) {
    this->totalReviews = reviews;
}

void Product::setManufacturer(const std::string& manufacturer) {
    this->manufacturer = manufacturer;
}

void Product::setYearReleased(int year) {
    this->yearReleased = year;
}

void Product::setIsActive(bool active) {
    this->isActive = active;
}

void Product::addTag(const std::string& tag) {
    if (std::find(tags.begin(), tags.end(), tag) == tags.end()) {
        tags.push_back(tag);
    }
}

void Product::updateRating(double newRating) {
    if (totalReviews == 0) {
        averageRating = newRating;
        totalReviews = 1;
    } else {
        averageRating = (averageRating * totalReviews + newRating) / (totalReviews + 1);
        totalReviews++;
    }
}

std::string Product::toString() const {
    std::stringstream ss;
    ss << "Product ID: " << id << "\n";
    ss << "Name: " << name << "\n";
    ss << "Category: " << category << "\n";
    ss << "Description: " << description << "\n";
    ss << "Price: " << Utils::formatCurrency(basePrice) << "\n";
    ss << "Stock: " << stockQuantity << "\n";
    ss << "Average Rating: " << averageRating << " (" << totalReviews << " reviews)\n";
    ss << "Manufacturer: " << manufacturer << "\n";
    ss << "Year released: " << yearReleased << "\n";
    ss << "Status: " << (isActive ? "Active" : "Inactive") << "\n";
    if (!tags.empty()) {
        ss << "Tags: " << Utils::join(tags, ", ") << "\n";
    }
    return ss.str();
}

std::string Product::toFileString() const {
    std::stringstream ss;
    ss << id << "|" << name << "|" << category << "|" << description << "|"
       << basePrice << "|" << stockQuantity << "|" << averageRating << "|"
       << totalReviews << "|" << manufacturer << "|" << yearReleased << "|"
       << (isActive ? 1 : 0) << "|" << Utils::join(tags, ",");

    return ss.str();
}

bool Product::matchesSearch(const std::string& query) const {
    std::string lowerQuery = Utils::toLowerCase(query);
    std::string lowerName = Utils::toLowerCase(name);
    std::string lowerCategory = Utils::toLowerCase(category);
    std::string lowerDescription = Utils::toLowerCase(description);
    std::string lowerManufacturer = Utils::toLowerCase(manufacturer);

    if (lowerName.find(lowerQuery) != std::string::npos) return true;
    if (lowerCategory.find(lowerQuery) != std::string::npos) return true;
    if (lowerDescription.find(lowerQuery) != std::string::npos) return true;
    if (lowerManufacturer.find(lowerQuery) != std::string::npos) return true;

    for (const auto& tag : tags) {
        if (Utils::toLowerCase(tag).find(lowerQuery) != std::string::npos) {
            return true;
        }
    }

    return false;
}