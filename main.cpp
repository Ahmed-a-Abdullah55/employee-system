#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class Employee {
public:
    int id;
    string name;
    double salary;

    Employee(int i, string n, double s) {
        id = i;
        name = n;
        salary = s;
    }
};

class EmployeeView {
public:
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void mainMenu() {
        cout << "\n--- Employee System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Edit Employee\n";
        cout << "3. Display All\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
    }

    void printEmployee(const Employee& e) const {
        cout << "ID: " << e.id << " | Name: " << e.name << " | Salary: " << e.salary << endl;
    }

    void showMessage(const string& msg) const {
        cout << ">> " << msg << endl;
    }

    void waitForEnter() {
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
};

class EmployeeController {
private:
    vector<Employee> employees;
    EmployeeView view;

    bool idExists(int id) const {
        for (const auto& e : employees) {
            if (e.id == id)
                return true;
        }
        return false;
    }

public:
    void addEmployee() {
        int id;
        string name;
        double salary;

        view.clearScreen();
        cout << "--- Add New Employee ---\n";
        cout << "Enter ID: "; cin >> id;

        if (idExists(id)) {
            view.showMessage("ID already exists! Please use a different ID.");
            view.waitForEnter();
            return;
        }

        cout << "Enter Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter Salary: "; cin >> salary;

        employees.push_back(Employee(id, name, salary));
        view.showMessage("Added successfully!");
        view.waitForEnter();
    }

    void editEmployee() {
        if (employees.empty()) {
            view.clearScreen();
            view.showMessage("No employees to edit.");
            view.waitForEnter();
            return;
        }

        view.clearScreen();
        int id;
        cout << "--- Edit Employee ---\n";
        cout << "Enter ID to edit: "; cin >> id;

        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].id == id) {
                cout << "Enter new name: "; cin.ignore(); getline(cin, employees[i].name);
                cout << "Enter new salary: "; cin >> employees[i].salary;
                view.showMessage("Updated successfully!");
                view.waitForEnter();
                return;
            }
        }
        view.showMessage("Employee not found!");
        view.waitForEnter();
    }

    void displayAll() {
        view.clearScreen();
        cout << "--- All Employees ---\n";
        if (employees.empty()) {
            view.showMessage("No data found.");
        }
        else {
            for (const auto& e : employees) {
                view.printEmployee(e);
            }
        }
        view.waitForEnter();
    }

    void start() {
        int choice;
        while (true) {
            view.mainMenu();
            cin >> choice;

            switch (choice) {
            case 1: addEmployee(); break;
            case 2: editEmployee(); break;
            case 3: displayAll(); break;
            case 4:
                view.clearScreen();
                view.showMessage("Goodbye!");
                return;
            default:
                view.showMessage("Invalid choice! Try again.");
                view.waitForEnter();
            }
        }
    }
};

int main() {
    EmployeeController controller;
    controller.start();
    return 0;
}