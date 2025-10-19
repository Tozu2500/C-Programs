#include "Review.h"
#include "Utils.h"
#include <sstream>
#include <ctime>

Review::Review() : id(0), productId(0), userId(0), userName(""), rating(0.0),
                    title(""), content(""), timestamp(0), helpfulCount(0),
                    notHelpfulCount(0), verified(false), reviewerLocation(""),
                    reviewLength(0) {}

Review::Review(int id, int productId, int userId, const std::string& userName,
                double rating, const std::string& title, const std::string& content)
    : id(id), productId(productId), userId(userId), userName(userName),
        rating(rating), title(title), content(content), helpfulCount(0),
        notHelpfulCount(0), verified(false), reviewerLocation("") {
    timestamp = std::time(nullptr);
    reviewLength = content.length();
}

int Review::getId() const {
    return id;
}

int Review::getProductId() const {
    return productId;
}

int Review::getUserId() const {
    return userId;
}

std::string Review::getUserName() const {
    return userName;
}

double Review::getRating() const {
    return rating;
}

std::string Review::getTitle() const {
    return title;
}

std::string Review::getContent() const {
    return content;
}

time_t Review::getTimestamp() const {
    return timestamp;
}

int Review::getHelpfulCount() const {
    return helpfulCount;
}

int Review::getNotHelpfulCount() const {
    return notHelpfulCount;
}

bool Review::isVerified() const {
    return verified;
}

std::string Review::getReviewerLocation() const {
    return reviewerLocation;
}

int Review::getReviewLength() const {
    return reviewLength;
}

void Review::setId(int id) {
    this->id = id;
}

void Review::setProductId(int productId) {
    this->productId = productId;
}

void Review::setUserId(int userId) {
    this->userId = userId;
}

void Review::setUserName(const std::string& userName) {
    this->userName = userName;
}

void Review::setRating(double rating) {
    this->rating = rating;
}

void Review::setTitle(const std::string& title) {
    this->title = title;
}

void Review::setContent(const std::string& content) {
    this->content = content;
    this->reviewLength = content.length();
}

void Review::setTimestamp(time_t timestamp) {
    this->timestamp = timestamp;
}

void Review::setHelpfulCount(int count) {
    this->helpfulCount = count;
}

void Review::setNotHelpfulCount(int count) {
    this->notHelpfulCount = count;
}

void Review::setVerified(bool verified) {
    this->verified = verified;
}

void Review::setReviewerLocation(const std::string& location) {
    this->reviewerLocation = location;
}

void Review::incrementHelpful() {
    helpfulCount++;
}

void Review::incrementNotHelpful() {
    notHelpfulCount++;
}

double Review::getHelpfulRatio() const {
    int total = helpfulCount + notHelpfulCount;
    if (total == 0) return 0.0;
    return static_cast<double>(helpfulCount) / total;
}

std::string Review::getFormattedDate() const {
    return Utils::formatTimestamp(timestamp);
}

std::string Review::toString() const {
    std::stringstream ss;
    ss << "Review ID: " << id << "\n";
    ss << "Product ID: " << productId << "\n";
    ss << "Reviewer: " << userName;
    if (verified) ss << " (Verified purchase)";
    ss << "\n";
    ss << "Rating: " << rating << " / 5.0\n";
    ss << "Title: " << title << "\n";
    ss << "Content: " << content << "\n";
    ss << "Date: " << getFormattedDate() << "\n";
    ss << "Helpful: " << helpfulCount << " | Not Helpful: " << notHelpfulCount << "\n";
    if (!reviewerLocation.empty()) {
        ss << "Location: " << reviewerLocation << "\n";
    }
    return ss.str();
}

std::string Review::toFileString() const {
    std::stringstream ss;
    ss << id << "|" << productId << "|" << userId << "|" << userName << "|"
       << rating << "|" << title << "|" << content << "|" << timestamp << "|"
       << helpfulCount << "|" << notHelpfulCount << "|" << (verified ? 1 : 0) << "|"
       << reviewerLocation << "|" << reviewLength;
    return ss.str();
}