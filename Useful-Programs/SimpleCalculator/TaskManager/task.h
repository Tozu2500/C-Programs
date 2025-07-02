#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

enum class Status {
    PENDING,
    IN_PROGRESS,
    COMPLETED
};

class Task {
private:
    static int nextId;
    int id;
    std::string title;
    std::string description;
    Priority priority;
    Status status;
    std::time_t createdAt;
    std::time_t dueDate;

public:
    // Constructors
    Task();
    Task(const std::string& title, const std::string& description, Priority priority = Priority::MEDIUM, std::time_t dueDate = 0);

    // Getters
    int getId() const {
        return id;
    }

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getDescription() const {
        return description;
    }

    Priority getPriority() const {
        return priority;
    }
    
    Status getStatus() const {
        return status;
    }

    std::time_t getCreatedAt() const {
        return createdAt;
    }

    std::time_t getDueDate() const {
        return dueDate;
    }

    // Setters
    void setTitle(const std::string& title) {
        this->title = title;
    }

    void setDescription(const std::string& description) {
        this->description = description;
    }

    void setPriority(Priority priority) {
        this->priority = priority;
    }

    void setStatus(Status status) {
        this->status = status;
    }

    void setDueDate(std::time_t dueDate) {
        this->dueDate = dueDate;
    }

    // File loading
    void setId(int newId) {
        id = newId;
    }

    void setCreatedAt(std::time_t t) {
        createdAt = t;
    }

    // Util methods
    std::string getPriorityString() const;
    std::string getStatusString() const;
    std::string getFormattedDate(std::time_t timestamp) const;
    bool isOverdue() const;

    // Display
    void display() const;
    std::string toString() const;
};

#endif // TASK_H