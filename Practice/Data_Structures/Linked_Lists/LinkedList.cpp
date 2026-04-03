#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedList {
    struct Node {
        T data;
        Node* next = nullptr;
        Node(T val) : data(val) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t sz = 0;

public:
    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push_back(T val) {
        Node* n = new Node(val);
        if (!tail) head = tail = n;
        else {
            tail->next = n;
            tail = n;
        }
        ++sz;
    }

    void pop_front() {
        if (!head) {
            throw std::underflow_error("The list is empty!");
        }

        Node* tmp = head;
        head = head->next;
        
        if (!head) {
            tail = nullptr;
        }
        delete tmp;
        --sz;
    }

    size_t size() const {
        return sz;
    }

    struct Iterator {
        Node* cur;
        Iterator(Node* n) : cur(n) {}
        T& operator*() {
            return cur->data;
        }

        Iterator& operator++() {
            cur = cur->next;
            return *this;
        }

        bool operator != (const Iterator& o) const {
            return cur != o.cur;
        };
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

int main() {
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) {
        list.push_back(i * 10);
    }

    std::cout << "List: ";
    for (int val : list) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    list.pop_front();
    std::cout << "After pop_front: ";
    for (int val : list) {
        std::cout << val << " ";
    }
    std::cout << "\nSize: " << list.size() << "\n";

    return 0;
}