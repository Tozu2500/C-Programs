#include <iostream>

using namespace std;

int main() {
    double num1;
    double num2;
    char operation;

    cout << "Enter your first number: ";
    cin >> num1;
    cout << "Enter the operation (+, -, *, /): ";
    cin >> operation;
    cout << "Enter the second number: ";
    cin >> num2;

    switch (operation) {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            break;
        case '-':
            cout << "Result: " << num1 - num2 << endl;
            break;
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            break;
        case '/':
            if (num2 != 0) {
                cout << "Result: " << num1 / num2 << endl;
            } else {
                cout << "Error: You cannot divide by zero!" << endl;
            }
            break;
        default:
            cout << "Invalid operation" << endl;
    }

    return 0;
}