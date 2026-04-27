#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include "todo.h"

class TodoList {
private:
    std::vector<Todo> todos;

public:
    void addTodo(const std::string& text);
    void removeTodo(int index);
    void markTodoCompleted(int index);
    void displayTodos() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    int size() const;
};

#endif // TODOLIST_H