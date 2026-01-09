#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to find all divisors of a number (excluding the number itself)
vector<int> getDivisors(int n) {
    vector<int> divisors;

    // Check the divisors up to sqrt(n)
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            divisors.push_back(i);

            // Add the divisor if it's different
            if (i != n / i && n / i != n) {
                divisors.push_back(n / i);
            }
        }
    }

    return divisors;
}

// Function to check if a number is perfect
bool isPerfect(int n) {
    if (n <= 1) return false;

    vector<int> divisors = getDivisors(n);
    int sum = 0;

    for (int divisor : divisors) {
        sum += divisor;
    }

    return sum == n;
}

// Function to display the divisors
void displayDivisors(int n) {
    vector<int> divisors = getDivisors(n);
    int sum = 0;

    cout << "Divisors of " << n << ": ";
    for (size_t i = 0; i < divisors.size(); i++) {
        cout << divisors[i];
        sum += divisors[i];
        if (i < divisors.size() - 1) cout << " + ";
    }
    cout << " = " << sum << endl;
}

// Function to find all perfect numbers up to a limit
void findPerfectNumbers(int limit) {
    cout << "\nPerfect Numbers up to " << limit << " " << endl;
    cout << "\nA perfect number is a positive integer that equals the sum of its proper divisors.\n" << endl;

    int count = 0;
    
    for (int i = 2; i <= limit; i++) {
        if (isPerfect(i)) {
            count++;
            cout << "Perfect Number #" << count << ": " << i << endl;
            displayDivisors(i);
            cout << endl;
        }
    }

    if (count == 0) {
        cout << "No perfect numbers found in this range." << endl;
    } else {
        cout << "Total perfect numbers found: " << count << endl;
    }
}

int main() {

    int choice, num, limit;

    cout << "====================" << endl;
    cout << "Perfect Number Finder" << endl;
    cout << "====================" << endl;

    while (true) {
        cout << "\nMenu" << endl;
        cout << "1. Check if a specific number is perfect" << endl;
        cout << "2. Find all perfect numbers up to a limit" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter a number to check: ";
                cin >> num;

                if (num <= 0) {
                    cout << "Please enter a positive number" << endl;
                } else if (isPerfect(num)) {
                    cout << "\n" << num << " is a PERFECT number!" << endl;
                    displayDivisors(num);
                } else {
                    cout << "\n" << num << " is NOT a perfect number" << endl;
                    displayDivisors(num);
                }
                break;
            
            case 2:
                cout << "\nEnter the upper limit: ";
                cin >> limit;

                if (limit <= 0) {
                    cout << "Please enter a positive number" << endl;
                } else {
                    findPerfectNumbers(limit);
                    cout << "\nNote: The first four perfect numbers are 6, 28, 496, and 8128." << endl;
                }
                break;

            case 3:
                cout << "\nThank you for using the perfect number finder!" << endl;
                return 0;
        
            default:
                cout << "Invalid choice, try again!" << endl;
        }
    }

    return 0;
}