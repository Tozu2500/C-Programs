#include "TaskManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

TaskManager::TaskManager(const std::string& filename) : filename(filename) {
    loadFromFile();
}

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
    std::cout << "Task added successfully!" << std::endl;
}

bool TaskManager::removeTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                [id](const Task& task) {
                    return task.getId() == id;
                });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Task removed successfully!" << std::endl;
        return true;
    }
    std::cout << "Task with an ID " << id << " was not found" << std::endl;
    return false;
}

Task* TaskManager::findTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                [id](const Task& task) {
                    return task.getId() == id;
                });
    return (it != tasks.end()) ? &(*it) : nullptr;
}

bool TaskManager::markCompleted(int id) {
    Task* task = findTask(id);
    if (task) {
        task->setStatus(Status::COMPLETED);
        std::cout << "Task marked as complete!" << std::endl;
        return true;
    }
    std::cout << "Task with an ID of " << id << " was not found" << std::endl;
    return false;
}

bool TaskManager::markInProgress(int id) {
    Task* task = findTask(id);
    if(task) {
        task->setStatus(Status::IN_PROGRESS);
        std::cout << "Task marked as in progress!" << std::endl;
        return true;
    }
    std::cout << "Task with an ID of " << id << " was not  found!" << std::endl;
    return false;
}

bool TaskManager::updateTask(int id, const std::string& title, const std::string& description, Priority priority) {
    Task* task = findTask(id);
    if (task) {
        task->setTitle(title);
        task->setDescription(description);
        task->setPriority(priority);
        std::cout << "Task updated successfully!" << std::endl;
        return true;
    }
    std::cout << "Task with an ID of " << id << " was not found!" << std::endl;
    return false;
}

void TaskManager::displayAllTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found!" << std::endl;
        return;
    }

    std::cout << "\n--- All Tasks ---" << std::endl;
    for (const auto& task : tasks) {
        task.display();
    }
}

void TaskManager::displayTasksByStatus(Status status) const {
    std::cout << "\n--- Tasks by Status ---" << std::endl;
    bool found = false;
    for (const auto& task: tasks) {
        if (task.getStatus() == status) {
            task.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No tasks found with the specified status" << std::endl;
    }
}

void TaskManager::displayTasksByPriority(Priority priority) const {
    std::cout << "\n--- Tasks by Priority ---" << std::endl;
    bool found = false;
    for (const auto& task : tasks) {
        if (task.getPriority() == priority) {
            task.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No tasks found with the specified priority!" << std::endl;
    }
}

void TaskManager::displayOverdueTasks() const {
    std::cout << "\n--- Overdue Tasks ---" << std::endl;
    bool found = false;
    for (const auto& task : tasks) {
        if (task.isOverdue()) {
            task.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No overdue tasks found!" << std::endl;
    }
}

bool TaskManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open the file for writing!" << std::endl;
        return false;
    }

    for (const auto& task : tasks) {
        file << task.toString() << std::endl;
    }

    file.close();
    return true;
}

bool TaskManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; // File does not exist yet
    }

    tasks.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, '|')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 7) {
            // parse fields
            int id = std::stoi(tokens[0]);
            std::string title = tokens[1];
            std::string description = tokens[2];
            int priorityInt = std::stoi(tokens[3]);
            int statusInt = std::stoi(tokens[4]);
            std::time_t createdAt = static_cast<std::time_t>(std::stoll(tokens[5]));
            std::time_t dueDate = static_cast<std::time_t>(std::stoll(tokens[6]));

            // Create task using setters
            Task task(title, description, static_cast<Priority>(priorityInt), dueDate);
            task.setId(id);
            task.setStatus(static_cast<Status>(statusInt));
            task.setCreatedAt(createdAt);

            tasks.push_back(task);
        }
    }
    file.close();
    return true;
}

int TaskManager::getCompletedTasks() const {
    return std::count_if(tasks.begin(), tasks.end(),
        [](const Task& task) {
            return task.getStatus() == Status::COMPLETED;
        });
}

int TaskManager::getPendingTasks() const {
    return std::count_if(tasks.begin(), tasks.end(),
            [](const Task& task) {
                return task.getStatus() == Status::PENDING;
            });
}

int TaskManager::getOverdueTasks() const {
    return std::count_if(tasks.begin(), tasks.end(),
            [](const Task& task) {
                return task.isOverdue();
            });
}

void TaskManager::clearAllTasks() {
    tasks.clear();
    std::cout << "All tasks cleared!" << std::endl;
}

std::vector<Task> TaskManager::searchTasks(const std::string& searchTerm) const {
    std::vector<Task> results;
    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(),
                    lowerSearchTerm.begin(), ::tolower);

    for (const auto& task : tasks) {
        std::string lowerTitle = task.getTitle();
        std::string lowerDesc = task.getDescription();
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        std::transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);

        if (lowerTitle.find(lowerSearchTerm) != std::string::npos ||
            lowerDesc.find(lowerSearchTerm) != std::string::npos) {
                results.push_back(task);
            } 
    }
    
    return results;
}