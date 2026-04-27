#include <iostream>
#include "todolist.h"

void showMenu() {
    std::cout << "\n To-Do Application \n";
    std::cout << "1. Add a task\n";
    std::cout << "2. Mark a task as completed\n";
    std::cout << "3. Remove a task\n";
    std::cout << "4. Show all tasks\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    TodoList list;
    list.loadFromFile("todos.txt");

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) {
            list.saveToFile("todos.txt");
            break;
        }

        if (choice == 1) {
            std::string text;
            std::cout << "Task description: ";
            std::getline(std::cin, text);
            list.addTodo(text);
        }

        if (choice == 2) {
            list.displayTodos();
            int index;
            std::cout << "Task number: ";
            std::cin >> index;
            list.markTodoCompleted(index - 1);
        }

        if (choice == 3) {
            list.displayTodos();
            int index;
            std::cout << "Task number: ";
            std::cin >> index;
            list.removeTodo(index - 1);
        }

        else if (choice == 4) {
            list.displayTodos();
        }
    }

    return 0;
}