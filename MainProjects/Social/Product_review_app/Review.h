#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include <ctime>

class Review {
private:
    int id;
    int productId;
    int userId;
    std::string userName;
    double rating;
    std::string title;
    std::string content;
    time_t timestamp;
    int helpfulCount;
    int notHelpfulCount;
    bool verified;
    std::string reviewerLocation;
    int reviewLength;

public:
    Review();
    Review(int id, int productId, int userId, const std::string& userName, 
           double rating, const std::string& title, const std::string& content);
    
    int getId() const;
    int getProductId() const;
    int getUserId() const;
    std::string getUserName() const;
    double getRating() const;
    std::string getTitle() const;
    std::string getContent() const;
    time_t getTimestamp() const;
    int getHelpfulCount() const;
    int getNotHelpfulCount() const;
    bool isVerified() const;
    std::string getReviewerLocation() const;
    int getReviewLength() const;
    
    void setId(int id);
    void setProductId(int productId);
    void setUserId(int userId);
    void setUserName(const std::string& userName);
    void setRating(double rating);
    void setTitle(const std::string& title);
    void setContent(const std::string& content);
    void setTimestamp(time_t timestamp);
    void setHelpfulCount(int count);
    void setNotHelpfulCount(int count);
    void setVerified(bool verified);
    void setReviewerLocation(const std::string& location);
    
    void incrementHelpful();
    void incrementNotHelpful();
    double getHelpfulRatio() const;
    std::string getFormattedDate() const;
    std::string toString() const;
    std::string toFileString() const;
};

#endif