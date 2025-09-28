#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdlib>

long performAddition(int num1, int num2);
long performSubtraction(int num1, int num2);
long performDivision(int num1, int num2);
long performMultiplication(int num1, int num2);

int main() {

    std::unordered_map<int, std::string> operations = {
        {1, "add"},
        {2, "subtract"},
        {3, "divide"},
        {4, "multiply"}
    };

    int choice = 0;

    int number1;
    int number2;
    long answer;

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Welcome to the Console Calculator!" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Which operation would you like to perform?" << std::endl;
    std::cout << "1 = Addition\n2 = Subtraction\n3 = Division\n4 = Multiplication" << std::endl;

    std::cin >> choice;
    
    switch (choice) {
        case 1:
            std::cout << "You chose addition" << std::endl;;
            std::cout << "Enter the first number: " << std::endl;
            std::cin >> number1;
            std::cout << "Enter the second number: " << std::endl;
            std::cin >> number2;
            answer = performAddition(number1, number2);
            std::cout << "Answer: " << answer << std::endl;
            break;
        case 2:
            std::cout << "You chose subtraction" << std::endl;
            std::cout << "Enter the first number: " << std::endl;
            std::cin >> number1;
            std::cout << "Enter the second number: " << std::endl;
            std::cin >> number2;
            answer = performSubtraction(number1, number2);
            std::cout << "Answer: " << answer << std::endl;
            break;
        case 3:
            std::cout << "You chose division" << std::endl;
            std::cout << "Enter the first number: " << std::endl;
            std::cin >> number1;
            std::cout << "Enter the second number: " << std::endl;
            std::cin >> number2;
            answer = performDivision(number1, number2);
            std::cout << "Answer: " << answer << std::endl;
            break;
        case 4:
            std::cout << "You chose multiplication" << std::endl;
            std::cout << "Enter the fisrt number: " << std::endl;
            std::cin >> number1;
            std::cout << "Enter the second number: " << std::endl;
            std::cin >> number2;
            answer = performMultiplication(number1, number2);
            std::cout << "Answer: " << answer << std::endl;
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            break;       
    }

    return 0;
}

long performAddition(int number1, int number2) {
    return number1 + number2;
}

long performSubtraction(int number1, int number2) {
    return number1 - number2;
}

long performDivision(int number1, int number2) {
    if (number2 == 0) {
        std::cout << "You cannot divide by zero!" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        return number1 / number2;
    }
}

long performMultiplication(int number1, int number2) {
    return number1 * number2;
}