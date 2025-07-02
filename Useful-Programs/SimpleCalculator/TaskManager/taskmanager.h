#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <string>
#include <functional>

class TaskManager {
private:
    std::vector<Task> tasks;
    std::string filename;

public:
    // Constructor
    TaskManager(const std::string& filename = "tasks.txt");

    // Task management
    void addTask(const Task& task);
    bool removeTask(int id);
    Task* findTask(int id);

    // Task operations
    bool markCompleted(int id);
    bool markInProgress(int id);
    bool updateTask(int id, const std::string& title, const std::string& description, Priority priority);

    // Display and filter
    void displayAllTasks() const;
    void displayTasksByStatus(Status status) const;
    void displayTasksByPriority(Priority priority) const;
    void displayOverdueTasks() const;

    // File operations
    bool saveToFile() const;
    bool loadFromFile();

    // Stats
    int getTotalTasks() const {
        return tasks.size();
    }

    int getCompletedTasks() const;
    int getPendingTasks() const;
    int getOverdueTasks() const;

    // Util
    void clearAllTasks();
    std::vector<Task> searchTasks(const std::string& searchTerm) const;
};

#endif // TASKMANAGER_H