
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

class Student {
private:
    int rollNo;
    char name[50];
    float marks;

public:

    // Safe Integer Input
    int safeIntInput() {
        int value;

        while (true) {
            cin >> value;

            if (cin.fail()) {
                cout << "Invalid Input! Please Enter a Valid Number: ";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                return value;
            }
        }
    }

    // Safe Float Input
    float safeFloatInput() {
        float value;

        while (true) {
            cin >> value;

            if (cin.fail()) {
                cout << "Invalid Input! Please Enter Valid Marks: ";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                return value;
            }
        }
    }

    // Input Student Details
    void input() {

        cout << "\nEnter Roll Number: ";
        rollNo = safeIntInput();

        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Marks: ";
        marks = safeFloatInput();
    }

    // Display Student Details
    void display() const {

        cout << left << setw(10) << rollNo
             << setw(25) << name
             << setw(10) << marks << endl;
    }

    // Getter
    int getRollNo() const {
        return rollNo;
    }

    // Update Student Details
    void update() {

        cin.ignore();

        cout << "Enter New Name: ";
        cin.getline(name, 50);

        cout << "Enter New Marks: ";
        marks = safeFloatInput();
    }
};

// Add Student
void addStudent() {

    Student s;

    ofstream file("students.dat", ios::binary | ios::app);

    if (!file) {
        cout << "\nError Opening File!\n";
        return;
    }

    s.input();

    file.write(reinterpret_cast<char*>(&s), sizeof(s));

    file.close();

    cout << "\nStudent Record Added Successfully!\n";
}

// Display All Students
void displayStudents() {

    Student s;

    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n--------------------------------------------------\n";
    cout << left << setw(10) << "RollNo"
         << setw(25) << "Name"
         << setw(10) << "Marks" << endl;

    cout << "--------------------------------------------------\n";

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent() {

    Student s;

    int roll;
    bool found = false;

    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\nEnter Roll Number to Search: ";

    while (!(cin >> roll)) {

        cout << "Invalid Input! Please Enter a Valid Roll Number: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {

        if (s.getRollNo() == roll) {

            cout << "\nStudent Found:\n";

            cout << "--------------------------------------------------\n";

            cout << left << setw(10) << "RollNo"
                 << setw(25) << "Name"
                 << setw(10) << "Marks" << endl;

            cout << "--------------------------------------------------\n";

            s.display();

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}

// Update Student
void updateStudent() {

    Student s;

    int roll;
    bool found = false;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "\nFile Not Found!\n";
        return;
    }

    cout << "\nEnter Roll Number to Update: ";

    while (!(cin >> roll)) {

        cout << "Invalid Input! Please Enter a Valid Roll Number: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {

        if (s.getRollNo() == roll) {

            cout << "\nCurrent Record Found!\n";
            cout << "Enter New Details:\n";

            s.update();

            streampos pos = -static_cast<streampos>(sizeof(s));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&s), sizeof(s));

            cout << "\nRecord Updated Successfully!\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}

// Delete Student
void deleteStudent() {

    Student s;

    int roll;
    bool found = false;

    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nFile Not Found!\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Roll Number to Delete: ";

    while (!(cin >> roll)) {

        cout << "Invalid Input! Please Enter a Valid Roll Number: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {

        if (s.getRollNo() == roll) {
            found = true;
        }
        else {
            temp.write(reinterpret_cast<char*>(&s), sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        cout << "\nRecord Deleted Successfully!\n";
    }
    else {
        cout << "\nStudent Not Found!\n";
    }
}

// Main Function
int main() {

    int choice;

    do {

        cout << "\n========== Student Management System ==========\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "Enter Your Choice: ";

        while (!(cin >> choice)) {

            cout << "Invalid Input! Please Enter a Number Between 1 to 6: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}

