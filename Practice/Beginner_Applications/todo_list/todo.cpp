#include "todo.h"

Todo::Todo() : description(""), completed(false) {}

Todo::Todo(const std::string& desc, bool done)
    : description(desc), completed(done) {}

std::string Todo::getDescription() const {
    return description;
}

bool Todo::isCompleted() const {
    return completed;
}

void Todo::markCompleted() {
    completed = true;
}

std::string Todo::toFileString() const {
    return (completed ? "1 |" : "0|") + description;
}