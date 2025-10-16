/*
    Custom String class

    Implementing a basic string class with proper memory management.
    Includes: constructors, destructor, copy/move semantics and operators.
*/
#include <cstring>
#include <iostream>

class MyString {
    char* data_;
    size_t size_;

public:
    MyString() : data_(nullptr), size_(0) {}

    MyString(const char* str) {
        size_ = strlen(str);
        data_ = new char[size_ + 1];
        strcpy(data_, str);
    }

    // Copy constructor
    MyString(const MyString& other) : size_(other.size_) {
        data_ = new char[size_ + 1];
        strcpy(data_, other.data_);
    }

    // Move constructor
    MyString(MyString&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // Copy assignment
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new char[size_ + 1];
            strcpy(data_, other.data_);
        }
        return *this;
    }

    // Move assignment
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Destructor
    ~MyString() {
        delete[] data_;
    }

    // Operator +
    MyString operator+(const MyString& rhs) const {
        size_t new_size = size_ + rhs.size_;
        char* new_data = new char[new_size + 1];
        strcpy(new_data, data_);
        strcpy(new_data, rhs.data_);
        MyString result(new_data);
        delete[] new_data;
        return result;
    }

    // Operator ==
    bool operator==(const MyString& rhs) const {
        if (size_ != rhs.size_) return false;
        return strcmp(data_, rhs.data_) == 0;
    }

    // Operator []
    char& operator[](size_t idx) {
        return data_[idx];
    }
    const char& operator[](size_t idx) const {
        return data_[idx];
    }

    // Operator <<
    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        if (str.data_) os << str.data_;
        return os;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2("World");
    MyString s3 = s1 + MyString(", ") + s2 + MyString("!");

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;

    // Copy constructor
    MyString s4 = s3;
    std::cout << "s4 (copy of s3): " << s4 << std::endl;

    // Move constructor
    MyString s5 = std::move(s4);
    std::cout << "s5 (moved from s4): " << s5 << std::endl;

    // Assignment operator
    s2 = s1;
    std::cout << "s2 (after assignment from s1): " << s2 << std::endl;

    // Move assignment
    s2 = std::move(s5);
    std::cout << "s2 (after move assignment from s5): " << s2 << std::endl;

    // Operator==
    std::cout << "s1 == s2? " << (s1 == s2 ? "true" : "false") << std::endl;

    // Operator[]
    if (s3[0] != '\0') {
        std::cout << "First character of s3: " << s3[0] << std::endl;
    }

    return 0;
}