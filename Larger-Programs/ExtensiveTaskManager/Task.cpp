#include "Task.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Static member init
int Task::nextId = 1;

// Constructors
Task::Task() : id(nextId++), title(""), description(""),
                priority(Priority::MEDIUM), status(Status::PENDING),
                createdAt(std::chrono::system_clock::now()),
                dueDate(std::chrono::system_clock::now() + std::chrono::hours(24)) {}

Task::Task(const std::string& title, const std::string& description, Priority priority)
    : id(nextId++), title(title), description(description),
        priority(priority), status(Status::PENDING),
        createdAt(std::chrono::system_clock::now()),
        dueDate(std::chrono::system_clock::now() + std::chrono::hours(24)) {}

Task::Task(int id, const std::string& title, const std::string& description,
        Priority priority, Status status,
        const std::chrono::system_clock::time_point& createdAt,
        const std::chrono::system_clock::time_point& dueDate)
    : id(id), title(title), description(description),
    priority(priority), status(status), createdAt(createdAt), dueDate(dueDate) {
        if (id >= nextId) {
            nextId = id + 1;
        }
}

// Utils
std::string Task::priorityToString() const {
    switch (priority) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
        default: return "Unknown";
    }
}

std::string Task::statusToString() const {
    switch (status) {
        case Status::PENDING: return "Pending";
        case Status::IN_PROGRESS: return "In Progress";
        case Status::COMPLETED: return "Completed";
        default: return "Unknown";
    }
}

std::string Task::dateToString(const std::chrono::system_clock::time_point& timePoint) const {
    auto time_t = std::chrono::system_clock::to_time_t(timePoint);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool Task::isOverdue() const {
    return std::chrono::system_clock::now() > dueDate && status != Status::COMPLETED;
}

void Task::display() const {
    std::cout << "Task # " << id << " -------------------------";
    std::cout << "Task name: " << std::setw(40) << std::left << title << std::endl;
    std::cout << "Description: " << std::setw(31) << std::left << description << std::endl;
    std::cout << "Priority: " << std::setw(34) << std::left << priorityToString() << std::endl;
    std::cout << "Status: " << std::setw(36) << std::left << statusToString() << std::endl;
    std::cout << "Created at: " << std::setw(35) << std::left << dateToString(createdAt) << std::endl;
    std::cout << "Due date: " << std::setw(39) << std::left << dateToString(dueDate) << std::endl;
    if (isOverdue()) {
        std::cout << " --- OVERDUE TASKS --- " << std::endl;
    }
    std::cout << " ---------------------------------------------------" << std::endl;
}

