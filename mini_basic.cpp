/*
 * ==========================================
 *        STUDENT MANAGEMENT SYSTEM
 * ==========================================
 * Features: Add, Display, Search, Average, Delete
 * Storage : CSV File (students.csv)
 * Language: C++
 * ==========================================
 */

#include <iostream>
#include <fstream>
using namespace std;

/* ==========================================
   GLOBAL CONSTANTS & VARIABLES
   ========================================== */
const int MAX = 100;
int rolls[MAX], n = 0;
string names[MAX];
float marks[MAX];
char grades[MAX];

/* ==========================================
   FUNCTION: CALCULATE GRADE
   ========================================== */
char getGrade(float m) {
    if (m >= 90) return 'A';
    if (m >= 80) return 'B';
    if (m >= 70) return 'C';
    if (m >= 60) return 'D';
    if (m >= 50) return 'E';
    return 'F';
}

/* ==========================================
   FUNCTION: SAVE DATA TO CSV FILE
   ========================================== */
void saveToFile() {
    ofstream file("students.csv");
    file << "RollNumber,Name,Marks,Grade\n";
    for (int i = 0; i < n; i++)
        file << rolls[i] << "," << names[i] << "," 
             << marks[i] << "," << grades[i] << "\n";
    file.close();
}

/* ==========================================
   FUNCTION: LOAD DATA FROM CSV FILE
   ========================================== */
void loadFromFile() {
    ifstream file("students.csv");
    if (!file) return;

    string header;
    getline(file, header);

    while (file >> rolls[n]) {
        file.ignore();
        getline(file, names[n], ','); 
        file >> marks[n];
        file.ignore();
        file >> grades[n];
        n++;
    }
    file.close(); 
}

/* ==========================================
   FUNCTION: ADD NEW STUDENT
   ========================================== */
void addStudent() {
    if (n >= MAX) {
        cout << "Maximum limit reached!\n";
        return;
    }

    int roll;
    cout << "\nEnter Roll Number: ";
    cin >> roll;

    for (int i = 0; i < n; i++) {
        if (rolls[i] == roll) {
            cout << "Roll Number already exists!\n";
            return;
        }
    }

    rolls[n] = roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, names[n]);

    cout << "Enter Marks (0-100): ";
    cin >> marks[n];

    if (marks[n] < 0 || marks[n] > 100) {
        cout << "Invalid marks!\n";
        return;
    }

    grades[n] = getGrade(marks[n]);
    n++;
    saveToFile();
    cout << "Student added successfully!\n";
}

/* ==========================================
   FUNCTION: DISPLAY ALL STUDENTS
   ========================================== */
void displayAll() {
    if (n == 0) {
        cout << "\nNo students found!\n";
        return;
    }

    cout << "\n----- ALL STUDENTS -----\n";
    cout << "Roll\tName\t\t\tMarks\tGrade\n";

    for (int i = 0; i < n; i++)
        cout << rolls[i] << "\t" << names[i]
             << "\t\t" << marks[i]
             << "\t" << grades[i] << "\n";

    cout << "Total: " << n << " students\n";
}

/* ==========================================
   FUNCTION: SEARCH STUDENT BY ROLL NUMBER
   ========================================== */
void searchStudent() {
    if (n == 0) {
        cout << "\nNo students found!\n";
        return;
    }

    int roll;
    cout << "\nEnter Roll Number: ";
    cin >> roll;

    for (int i = 0; i < n; i++) {
        if (rolls[i] == roll) {
            cout << "\nRoll: " << rolls[i]
                 << "\nName: " << names[i]
                 << "\nMarks: " << marks[i]
                 << "\nGrade: " << grades[i] << "\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

/* ==========================================
   FUNCTION: CALCULATE AVERAGE & STATISTICS
   ========================================== */
void calcAverage() {
    if (n == 0) {
        cout << "\nNo students found!\n";
        return;
    }

    float total = 0;
    float highest = marks[0], lowest = marks[0];

    for (int i = 0; i < n; i++) {
        total += marks[i];
        if (marks[i] > highest) highest = marks[i];
        if (marks[i] < lowest) lowest = marks[i];
    }

    cout << "\n----- STATISTICS -----\n";
    cout << "Total Students: " << n << "\n";
    cout << "Average Marks: " << total / n << "\n";
    cout << "Highest Marks: " << highest << "\n";
    cout << "Lowest Marks: " << lowest << "\n";
}

/* ==========================================
   FUNCTION: DELETE STUDENT RECORD
   ========================================== */
void deleteStudent() {
    if (n == 0) {
        cout << "\nNo students found!\n";
        return;
    }

    int roll;
    cout << "\nEnter Roll Number: ";
    cin >> roll;

    for (int i = 0; i < n; i++) {
        if (rolls[i] == roll) {
            for (int j = i; j < n - 1; j++) {
                rolls[j] = rolls[j + 1];
                names[j] = names[j + 1];
                marks[j] = marks[j + 1];
                grades[j] = grades[j + 1];
            }
            n--;
            saveToFile();
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

/* ==========================================
   MAIN FUNCTION
   ========================================== */
int main() {
    int choice;
    cout << "\n=== STUDENT MANAGEMENT SYSTEM ===\n";

    loadFromFile();

    do {
        cout << "\n1.Add 2.Display 3.Search 4.Average 5.Delete 6.Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: calcAverage(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}

