#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>
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
        std::chrono::system_clock::time_point createdAt;
        std::chrono::system_clock::time_point dueDate;

    public:
        // Constructors
        Task();
        Task(const std::string& title, const std::string& description,
            Priority priority = Priority::MEDIUM);
        Task(int id, const std::string& title, const std::string& description,
            Priority priority, Status status,
            const std::chrono::system_clock::time_point& createdAt,
            const std::chrono::system_clock::time_point& dueDate);

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
        std::chrono::system_clock::time_point getCreatedAt() const {
            return createdAt;
        }
        std::chrono::system_clock::time_point getDueDate() const {
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

        void setDueDate(const std::chrono::system_clock::time_point& dueDate) {
            this->dueDate = dueDate;
        }

        // Utils
        std::string priorityToString() const;
        std::string statusToString() const;
        std::string dateToString(const std::chrono::system_clock::time_point& timePoint) const;
        bool isOverdue() const;

        // Display
        void display() const;
        std::string toString() const;

        // Serialization
        std::string serialize() const;
        static Task deserialize(const std::string& data);
};

#endif // TASK_H