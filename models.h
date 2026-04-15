#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <exception>
#include <iomanip>

using namespace std;

// Forward reference color constants (will be defined in dashboard.h usually, but we inject inline strings here for simplicity)
const string M_RESET = "\033[0m";
const string M_YELLOW = "\033[33m";
const string M_CYAN = "\033[36m";

class InvalidInputException : public exception {
    string msg;
public:
    InvalidInputException(const string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class Person {
protected:
    string id;  
    string name;

public:
    Person(string c_id, string c_name) : id(c_id), name(c_name) {}
    virtual ~Person() {}

    virtual void displayRow() const = 0;
    virtual string getType() const = 0;
    virtual string getDetails() const = 0;
    virtual string toCSV() const = 0;
    
    string getId() const { return id; }
    string getName() const { return name; }
};

class Student : public Person {
private:
    float gpa;
public:
    Student(string id, string name, float g) : Person(id, name), gpa(g) {}

    void displayRow() const override {
        cout << "| " << setw(8) << left << id 
             << " | " << setw(18) << left << name 
             << " | " << setw(10) << left << M_CYAN + "Student" + M_RESET
             << " | " << setw(20) << left << ("GPA: " + to_string(gpa).substr(0, 4)) << " |\n";
    }

    string getType() const override { return "Student"; }
    string getDetails() const override { return "GPA: " + to_string(gpa).substr(0, 4); }
    string toCSV() const override { return "Student," + id + "," + name + "," + to_string(gpa); }
    float getGpa() const { return gpa; }
};

class Faculty : public Person {
private:
    string department;
public:
    Faculty(string id, string name, string dept) : Person(id, name), department(dept) {}

    void displayRow() const override {
        cout << "| " << setw(8) << left << id 
             << " | " << setw(18) << left << name 
             << " | " << setw(10) << left << M_YELLOW + "Faculty" + M_RESET
             << " | " << setw(20) << left << ("Dept: " + department) << " |\n";
    }

    string getType() const override { return "Faculty"; }
    string getDetails() const override { return "Dept: " + department; }
    string toCSV() const override { return "Faculty," + id + "," + name + "," + department; }
    string getDepartment() const { return department; }
};

#endif
