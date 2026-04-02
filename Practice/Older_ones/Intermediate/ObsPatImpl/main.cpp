/*
    Observer Pattern Implementation

    Implementing the Observer design pattern with multiple observers
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// --- Observer Interface ---
class Observer {
public:
    virtual void update(int state) = 0;
    virtual ~Observer() = default;
};

// --- Subject Class ---
class Subject {
    std::vector<Observer*> observers_;
    int state_ = 0;  // ✅ initialize to avoid undefined behavior
    
public:
    void attach(Observer* obs) {
        // Prevent duplicate attachment
        if (std::find(observers_.begin(), observers_.end(), obs) == observers_.end()) {
            observers_.push_back(obs);
        }
    }
    
    void detach(Observer* obs) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), obs),
                         observers_.end());
    }
    
    void setState(int state) {
        state_ = state;
        notify();
    }
    
    void notify() const {
        for (auto obs : observers_) {
            if (obs) obs->update(state_);
        }
    }
};

class ConsoleObserver : public Observer {
    std::string name_;
public:
    explicit ConsoleObserver(const std::string& name) : name_(name) {}
    void update(int state) override {
        std::cout << "[" << name_ << "] received new state: " << state << std::endl;
    }
};

class SquareObserver : public Observer {
public:
    void update(int state) override {
        std::cout << "Square of state: " << (state * state) << std::endl;
    }
};

class DoubleObserver : public Observer {
public:
    void update(int state) override {
        std::cout << "Double of state: " << (state * 2) << std::endl;
    }
};

int main() {
    Subject subject;

    ConsoleObserver obs1("Observer1");
    ConsoleObserver obs2("Observer2");
    SquareObserver squareObs;
    DoubleObserver doubleObs;

    subject.attach(&obs1);
    subject.attach(&obs2);
    subject.attach(&squareObs);
    subject.attach(&doubleObs);

    std::cout << "Setting state to 5...\n";
    subject.setState(5);

    std::cout << "\nDetaching Observer2 and setting state to 10...\n";
    subject.detach(&obs2);
    subject.setState(10);

    std::cout << "\nDetaching SquareObserver and settings state to 3...\n";
    subject.detach(&squareObs);
    subject.setState(3);

    return 0;
}