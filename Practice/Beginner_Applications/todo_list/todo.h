#ifndef TODO_H
#define TODO_H

#include <string>

class Todo {
private:
    std::string description;
    bool completed;

public:
    Todo();
    Todo(const std::string& desc, bool done = false);

    std::string getDescription() const;
    bool isCompleted() const;

    void markCompleted();
    std::string toFileString() const;
};

#endif // TODO_H