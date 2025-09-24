#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
private:
    string name;
    int id;
    double gpa;
    string major;

public:
    Student(string n, int i, double g, string m) 
        : name(n), id(i), gpa(g), major(m) {}

    int getId() const {
        return id; 
    }

    string getName() const {
        return name; 
    }

    double getGpa() const {
         return gpa; 
    }

    string getMajor() const {
        return major; 
    }

    void display() const {
        cout << left << setw(10) << id 
             << setw(20) << name 
             << setw(10) << gpa 
             << setw(15) << major << endl;
    }

    void saveToFile(ofstream& out) const {
        out << id << "," << name << "," << gpa << "," << major << "\n";
    }

    static Student loadFromLine(const string& line) {
        string n, m;
        int i;
        double g;
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        i = stoi(line.substr(0, pos1));
        n = line.substr(pos1 + 1, pos2 - pos1 - 1);
        g = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
        m = line.substr(pos3 + 1);

        return Student(n, i, g, m);
    }
};

class StudentSystem {
private:
    vector<Student> students;
    string filename = "students.txt";

public:
    StudentSystem() { load(); }
    ~StudentSystem() { save(); }

    void addStudent() {
        string name, major;
        int id;
        double gpa;

        cout << "Enter ID: "; cin >> id;
        cout << "Enter Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter GPA: "; cin >> gpa;
        cout << "Enter Major: "; cin.ignore(); getline(cin, major);

        students.push_back(Student(name, id, gpa, major));
        cout << "Student added successfully.\n";
    }

    void displayAll() const {
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "GPA" 
             << setw(15) << "Major" << endl;
        cout << "------------------------------------------------------\n";
        for (const auto& s : students) s.display();
    }

    void searchStudent() const {
        int id;
        cout << "Enter ID to search: "; cin >> id;
        for (const auto& s : students) {
            if (s.getId() == id) {
                cout << "Student found:\n";
                s.display();
                return;
            }
        }
        cout << "No student found with ID " << id << ".\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter ID to delete: "; cin >> id;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getId() == id) {
                students.erase(it);
                cout << "Student deleted successfully.\n";
                return;
            }
        }
        cout << "No student found with ID " << id << ".\n";
    }

    void save() const {
        ofstream out(filename);
        for (const auto& s : students) s.saveToFile(out);
        out.close();
    }

    void load() {
        ifstream in(filename);
        string line;
        while (getline(in, line)) {
            if (!line.empty()) students.push_back(Student::loadFromLine(line));
        }
        in.close();
    }
};

int main() {
    StudentSystem system;
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Delete Student by ID\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addStudent(); break;
            case 2: system.displayAll(); break;
            case 3: system.searchStudent(); break;
            case 4: system.deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}