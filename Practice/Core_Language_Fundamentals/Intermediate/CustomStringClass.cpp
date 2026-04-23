#include <iostream>
#include <cstring>

/**
 * This class manages dynamically allocated C-style strings.
 * Implements:
 * -- Constructor
 * -- Copy constructor (deep copy)
 * -- Copy assignment operator (deep copy)
 * -- Destructor
 */
class MyString {
private:
    char* data;  // A pointer to dynamically allocated char array.
    size_t length;  // Length of the string, exluding the NULL TERMINATOR!

public:
    // Default constructor, that initializes an empty string.
    MyString() : data(nullptr), length(0) {}

    // Constructor from C-String
    // @param str Input null-terminated string
    MyString(const char* str) {
        if (str) {
            length = std::strlen(str);
            data = new char[length + 1];  // Add one for the null terminator
            std::strcpy(data, str);
        } else {
            data = nullptr;
            length = 0;
        }
    }

    /**
     * @brief Copy constructor - deep copy
     * @param other Another MyString object
     * 
     * Creates a completely independent copy of the string
     */
    MyString(const MyString& other) {
        length = other.length;

        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    /**
     * @brief Copy assignment operator
     * @param other Another MyString object
     * @return Reference to this object
     * 
     * Handle self-assignment and avoid memory leaks!
     */
    MyString& operator=(const MyString& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        length = other.length;

        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }

        return *this;
    }

    ~MyString() {
        delete[] data;
    }

    size_t size() const {
        return length;
    }

    const char* c_str() const {
        return data ? data : "";
    }

    char operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    void print() const {
        std::cout << c_str() << std::endl;
    }
};

int main() {
    std::cout << "Custom string class DEMO\n\n";

    MyString str1("Hello everyone!");
    std::cout << "str1: ";
    str1.print();

    // Copy constructor
    MyString str2 = str1;
    std::cout << "str2, copy of str1: \n";
    str2.print();

    // Modify the original string
    MyString str3("World");
    std::cout << "str3: ";
    str3.print();

    str2 = str3;
    std::cout << "str2 after assignment from str3: ";
    str2.print();

    std::cout << "\nstr3[1]: " << str3[1] << std::endl;

    std::cout << "\nProgram done!\n";
    
    return 0;
}