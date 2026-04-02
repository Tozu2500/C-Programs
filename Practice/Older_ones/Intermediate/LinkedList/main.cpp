/*
    Implementing a singly linked list using smart pointers (unique_ptr)
    Include: insert, remove, reverse and find
*/

#include <memory>
#include <iostream>

template<typename T>
class LinkedList {
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::unique_ptr<Node> head;

public:
    void insert(T val) {
        auto newNode = std::make_unique<Node>(val);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    bool remove(T val) {
        Node* prev = nullptr;
        Node* curr = head.get();
        while (curr) {
            if (curr->data == val) {
                if (prev) {
                    prev->next = std::move(curr->next);
                } else {
                    head = std::move(curr->next);
                }
                return true;
            }
            prev = curr;
            curr = curr->next.get();
        }
        return false;
    }

    bool find(T val) const {
        Node* curr = head.get();
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next.get();
        }
        return false;
    }

    void reverse() {
        std::unique_ptr<Node> prev = nullptr;
        while (head) {
            auto next = std::move(head->next);
            head->next = std::move(prev);
            prev = std::move(head);
            head = std::move(next);
        }
        head = std::move(prev);
    }

    void print() const {
        Node* curr = head.get();
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next.get();
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList<int> list;
    list.insert(3);
    list.insert(2);
    list.insert(1);
    std::cout << "List after insertions: ";
    list.print();

    std::cout << "Find 2: " << (list.find(2) ? "Found" : "Not found") << std::endl;
    std::cout << "Remove 2: " << (list.remove(2) ? "Removed" : "Not removed") << std::endl;
    std::cout << "List after removal: ";
    list.print();

    list.reverse();
    std::cout << "List after reverse: ";
    list.print();

    return 0;
}