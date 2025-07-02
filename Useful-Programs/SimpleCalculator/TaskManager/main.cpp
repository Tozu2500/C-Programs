#include "TaskManager.h"
#include "Task.h"
#include <iostream>
#include <string>
#include <ctime>

void displayMenu() {
    std::cout << "\n --- Task Manager ---" << std::endl;
    std::cout << "1. Add task" << std::endl;
    std::cout << "2. Display all tasks" << std::endl;
    std::cout << "3. Mark task as completed" << std::endl;
    std::cout << "4. Mark task as in progress" << std::endl;
    std::cout << "5. Remove task" << std::endl;
    std::cout << "6. Display tasks by status" << std::endl;
    std::cout << "7. Display tasks by priority" << std::endl;
    std::cout << "8. Display overdue tasks" << std::endl;
    std::cout << "9. Search tasks" << std::endl;
    std::cout << "10. Show statistics" << std::endl;
    std::cout << "11. Save tasks" << std::endl;
    std::cout << "0. Exit " << std::endl;
    std::cout << "Choice: ";
}

Priority getPriorityFromUser() {
    int choice;
    std::cout << "Priority (1 = Low, 2 = Medium, 3 = High): ";
    std::cin >> choice;

    switch(choice) {
        case 1: return Priority::LOW;
        case 2: return Priority::MEDIUM;
        case 3: return Priority::HIGH;
        default: return Priority::MEDIUM;
    }
}

Status getStatusFromUser() {
    int choice;
    std::cout << "Status (1 = Pending, 2 = In progress, 3 = Completed): ";
    std::cin >> choice;

    switch (choice) {
        case 1: return Status::PENDING;
        case 2: return Status::IN_PROGRESS;
        case 3: return Status::COMPLETED;
        default: return Status::PENDING;
    }
}

int main() {
    TaskManager manager("tasks.txt");
    int choice;

    std::cout << "Welcome to Task Manager!" << std::endl;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                std::string title, description;
                std:: cout << "Enter task title: ";
                std::getline(std::cin, title);
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);

                Priority priority = getPriorityFromUser();

                char hasDueDate;
                std::cout << "Set due date? (Y/N): ";
                std::cin >> hasDueDate;

                std::time_t dueDate = 0;
                if (hasDueDate == 'y' || hasDueDate == 'Y') {
                    int days;
                    std::cout << "Days from now: ";
                    std::cin >> days;
                    dueDate = std::time(nullptr) + (days * 24 * 60 * 60);
                }

                Task task(title, description, priority, dueDate);
                manager.addTask(task);
                break;
            }

            case 2: {
                manager.displayAllTasks();
                break;
            }

            case 3: {
                int id;
                std::cout << "Enter task ID to mark as completed: ";
                std::cin >> id;
                manager.markCompleted(id);
                break;
            }

            case 4: {
                int id;
                std::cout << "Enter task ID to mark as in progress: ";
                std::cin >> id;
                manager.markInProgress(id);
                break;
            }

            case 5: {
                int id;
                std::cout << "Enter task ID to remove: ";
                std::cin >> id;
                manager.removeTask(id);
                break;
            }

            case 6: {
                Status status = getStatusFromUser();
                manager.displayTasksByStatus(status);
                break;
            }

            case 7: {
                Priority priority = getPriorityFromUser();
                manager.displayTasksByPriority(priority);
                break;
            }

            case 8: {
                manager.displayOverdueTasks();
                break;
            }

            case 9: {
                std::string searchTerm;
                std::cout << "Enter search term: ";
                std::getline(std::cin, searchTerm);

                auto results = manager.searchTasks(searchTerm);
                if (results.empty()) {
                    std::cout << "No tasks found matching '" << searchTerm << "'" << std::endl;
                } else {
                    std::cout << "\n--- Search Results ---" << std::endl;
                    for (const auto& task : results) {
                        task.display();
                    }
                }
                break;
            }
            
            case 10: {
                std::cout << "\n--- Statistics ---" << std::endl;
                std::cout << "Ttotal tasks: " << manager.getTotalTasks() << std::endl;
                std::cout << "Completed tasks: " << manager.getCompletedTasks() << std::endl;
                std::cout << "pending tasks: " << manager.getPendingTasks() << std::endl;
                std::cout << "Overdue tasks: " << manager.getOverdueTasks() << std::endl;
                break;
            }

            case 11: {
                if (manager.saveToFile()) {
                    std::cout << "Tasks saved successfully!" << std::endl;
                } else {
                    std::cout << "Error saving tasks!" << std::endl;
                }
                break;
            }

            case 0:
                std::cout << "Savings tasks and exiting..." << std::endl;
                manager.saveToFile();
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }

    } while (choice != 0);

    std::cout << "Thank you for using the Task Manager!" << std::endl;
    return 0;
}