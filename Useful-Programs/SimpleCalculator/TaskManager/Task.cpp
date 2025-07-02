#include "Task.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int Task::nextId = 1;

Task::Task() : id(nextId++), title(""), description(""),
                priority(Priority::MEDIUM), status(Status::PENDING),
                createdAt(std::time(nullptr)), dueDate(0) {}

Task::Task(const std::string& title, const std::string& description,
            Priority priority, std::time_t dueDate)
        : id(nextId++), title(title), description(description),
            priority(priority), status(Status::PENDING),
            createdAt(std::time(nullptr)), dueDate(dueDate) {}

std::string Task::getPriorityString() const {
    switch (priority) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
        default: return "Unknown";
    }
}

std::string Task::getStatusString() const {
    switch (status) {
        case Status::PENDING: return "Pending";
        case Status::IN_PROGRESS: return "In Progress";
        case Status::COMPLETED: return "Completed";
        default: return "Unknown";
    }
}

std::string Task::getFormattedDate(std::time_t timestamp) const {
    if (timestamp == 0) return "Not set";

    std::tm* tm = std::localtime(&timestamp);
    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M");
    return ss.str();
}

bool Task::isOverdue() const {
    if (dueDate == 0 || status == Status::COMPLETED) return false;
    return std::time(nullptr) > dueDate;
}

void Task::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Description " << description << std::endl;
    std::cout << "Priority: " << getPriorityString() << std::endl;
    std::cout << "Status: " << getStatusString() << std::endl;
    std::cout << "Created: " << getFormattedDate(createdAt) << std::endl;
    std::cout << "Due date: " << getFormattedDate(dueDate) << std::endl;

    if (isOverdue()) {
        std::cout << "** OVERDUE **" << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

std::string Task::toString() const {
    std::stringstream ss;
    ss << id << "|" << title << "|" << description << "|"
       << static_cast<int>(priority) << "|" << static_cast<int>(status) << "|"
       << createdAt << "|" << dueDate;
    return ss.str();
}