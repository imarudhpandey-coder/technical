#include "dashboard.h"
#include <iostream>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
void enableVirtualTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void enableVirtualTerminal() {}
#endif

// Define colors
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";

void Dashboard::printHeader() {
    cout << CYAN << BOLD << "\n=======================================================================\n" << RESET;
    cout << BOLD << "                 UNIVERSITY MANAGEMENT SYSTEM DASHBOARD                \n" << RESET;
    cout << CYAN << BOLD << "=======================================================================\n" << RESET;
}

void Dashboard::printHeader(const string& subtitle) {
    cout << CYAN << BOLD << "\n=======================================================================\n" << RESET;
    int pad = (71 - subtitle.length()) / 2;
    cout << BOLD << string(pad, ' ') << subtitle << string(pad, ' ') << " \n" << RESET;
    cout << CYAN << BOLD << "=======================================================================\n" << RESET;
}

void Dashboard::displayMenu() {
    cout << YELLOW << "\n [" << RESET << BOLD << "1" << RESET << YELLOW << "]" << RESET << " Add New Student\n";
    cout << YELLOW << " [" << RESET << BOLD << "2" << RESET << YELLOW << "]" << RESET << " Add New Faculty\n";
    cout << YELLOW << " [" << RESET << BOLD << "3" << RESET << YELLOW << "]" << RESET << " View Complete Dashboard\n";
    cout << YELLOW << " [" << RESET << BOLD << "4" << RESET << YELLOW << "]" << RESET << " View Only Students\n";
    cout << YELLOW << " [" << RESET << BOLD << "5" << RESET << YELLOW << "]" << RESET << " View Only Faculty\n";
    cout << YELLOW << " [" << RESET << BOLD << "6" << RESET << YELLOW << "]" << RESET << " Search Record by ID\n";
    cout << YELLOW << " [" << RESET << BOLD << "7" << RESET << YELLOW << "]" << RESET << " Load Mock Data\n";
    cout << YELLOW << " [" << RESET << BOLD << "8" << RESET << YELLOW << "]" << RESET << " Save Data to File\n";
    cout << YELLOW << " [" << RESET << BOLD << "9" << RESET << YELLOW << "]" << RESET << " Exit\n";
    cout << "\n" << BOLD << GREEN << " >> " << RESET << "Select Action: ";
}

void Dashboard::displayRecords(const vector<shared_ptr<Person>>& records, const string& filter) {
    printHeader(filter == "All" ? "ALL RECORDS DASHBOARD" : (filter == "Student" ? "STUDENT RECORDS" : "FACULTY RECORDS"));
    
    cout << BOLD << "+----------+--------------------+------------+----------------------+\n";
    cout << "| ID       | Name               | Role       | Extra Details        |\n";
    cout << "+----------+--------------------+------------+----------------------+\n" << RESET;
    
    int count = 0;
    int students = 0, faculty = 0;

    for (const auto& person : records) {
        bool isStudent = dynamic_cast<Student*>(person.get()) != nullptr;
        bool isFaculty = dynamic_cast<Faculty*>(person.get()) != nullptr;

        if (isStudent) students++;
        if (isFaculty) faculty++;

        if (filter == "All" || (filter == "Student" && isStudent) || (filter == "Faculty" && isFaculty)) {
            person->displayRow();
            count++;
        }
    }

    if (count == 0) {
        string msg = filter == "All" ? "No records found in the system." : ("No " + filter + " records found.");
        cout << "| " << RED << setw(66) << left << msg << RESET << " |\n";
    }
    cout << BOLD << "+----------+--------------------+------------+----------------------+\n" << RESET;

    if (filter == "All") {
        cout << BLUE << "\n System Stats: " << BOLD << students << RESET << BLUE << " Student(s) | " 
             << BOLD << faculty << RESET << BLUE << " Faculty | " 
             << BOLD << records.size() << RESET << BLUE << " Total" << RESET << "\n";
    } else {
        cout << BLUE << "\n Valid Results: " << BOLD << count << RESET << "\n";
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
