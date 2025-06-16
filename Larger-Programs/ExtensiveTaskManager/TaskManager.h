#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <memory>
#include <functional>

class TaskManager {
private:
    std::vector<std::unique_ptr<Task>> tasks;
    std::string filename;

public:
    // Constructor
    explicit TaskManager(const std::string& filename = "tasks.txt");

    // Destructor
    ~TaskManager();

    // Task management system
    void addTask(const std::string& title, const std::string& description,
                Priority priority = Priority::MEDIUM);
    bool removeTask(int id);
    Task* findTask(int id);
    const Task* findTask(int id) const;

    // Task operation updates
    bool updateTaskStatus(int id, Status status);
    bool updateTaskPriority(int id, Priority priority);
    bool updateTaskTitle(int id, const std::string& title);
    bool updateTaskDescription(int id, const std::string& description);

    // Display and filters
    void displayAllTasks() const;
    void displayTasksByStatus(Status status) const;
    void displayTasksByPriority(Priority priority) const;
    void displayOverdueTasks() const;

    // Statistics functions
    int getTotalTaskCount() const;
    int getTaskCountByStatus(Status status) const;
    int getOverdueTaskCount() const;

    // Sorting functions
    void sortTasksByPriority();
    void sortTasksByDueDate();
    void sortTasksById();

    // File ops
    bool saveToFile() const;
    bool loadFromFile();

    // Util
    void clearAllTasks();
    bool isEmpty() const {
        return tasks.empty();
    }

private:
    // Helper
    void displayTasksFiltered(std::function<bool(const Task&)> filter) const;
};

#endif // TASKMANAGER_H