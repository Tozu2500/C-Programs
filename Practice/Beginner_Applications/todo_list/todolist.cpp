#include "todolist.h"
#include <iostream>
#include <fstream>

void TodoList::addTodo(const std::string& text) {
    todos.emplace_back(text);
}

void TodoList::removeTodo(int index) {
    if (index >= 0 && index < todos.size()) {
        todos.erase(todos.begin() + index);
    }
}

void TodoList::markTodoCompleted(int index) {
    if (index >= 0 && index < todos.size()) {
        todos[index].markCompleted();
    }
}

void TodoList::displayTodos() const {
    for (int i = 0; i < todos.size(); i++) {
        std::cout << i + 1 << ". ["
                << (todos[i].isCompleted() ? 'X' : ' ')
                << "]" << todos[i].getDescription() << "\n";
    }
}

int TodoList::size() const {
    return todos.size();
}

void TodoList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;

    todos.clear();
    std::string line;

    while (std::getline(file, line)) {
        bool done = line[0] == '1';
        std::string desc = line.substr(2);
        todos.emplace_back(desc, done);
    }
}

void TodoList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& todo : todos) {
        file << todo.toFileString() << "\n";
    }
}