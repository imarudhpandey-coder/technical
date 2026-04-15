#include <iostream>
#include <string>
#include <memory>
#include "models.h"
#include "repository.h"
#include "dashboard.h"
#include <cstdlib>
using namespace std;

int main() {
    //system("start index.html");  // opens browser

    // Enable colorful dashboard for Windows terminals
    enableVirtualTerminal();

    // Repository using templates
    Repository<Person> repo;
    repo.loadFromFile("university_data.txt");
    int choice = 0;

    while (choice != 9) {
        Dashboard::printHeader();
        Dashboard::displayMenu();

        if (!(cin >> choice)) {
            clearInput();
            cout << RED << " [!] Invalid input type. Please enter a number.\n" << RESET;
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    Dashboard::printHeader("NEW STUDENT ENROLLMENT");
                    string id, name;
                    float gpa;
                    cout << "   Enter Student ID: "; cin >> id;
                    cout << "   Enter Full Name: "; 
                    cin.ignore(); getline(cin, name);
                    cout << "   Enter GPA: "; 
                    if (!(cin >> gpa) || gpa < 0.0f || gpa > 10.0f) {
                        clearInput();
                        throw InvalidInputException("Invalid GPA! Must be numeric and between 0.0 and 10.0");
                    }
                    repo.add(make_shared<Student>(id, name, gpa));
                    cout << GREEN << BOLD << "\n [v] Student " << name << " added successfully!\n" << RESET;
                    break;
                }
                case 2: {
                    Dashboard::printHeader("NEW FACULTY ONBOARDING");
                    string id, name, dept;
                    cout << "   Enter Faculty ID: "; cin >> id;
                    cout << "   Enter Full Name: "; 
                    cin.ignore(); getline(cin, name);
                    cout << "   Enter Department: "; 
                    getline(cin, dept);
                    repo.add(make_shared<Faculty>(id, name, dept));
                    cout << GREEN << BOLD << "\n [v] Faculty " << name << " verified and added!\n" << RESET;
                    break;
                }
                case 3:
                    Dashboard::displayRecords(repo.getAll());
                    break;
                case 4:
                    Dashboard::displayRecords(repo.getAll(), "Student");
                    break;
                case 5:
                    Dashboard::displayRecords(repo.getAll(), "Faculty");
                    break;

                case 6: {
                    Dashboard::printHeader("SEARCH SYSTEM");
                    string searchId;
                    cout << "   Enter ID to search: "; cin >> searchId;
                    auto result = repo.findById(searchId);
                    if (result) {
                        cout << GREEN << BOLD << "\n [v] Record Found:\n" << RESET;
                        cout << "     Name: " << result->getName() << "\n";
                        cout << "     Role: " << result->getType() << "\n";
                        cout << "     Info: " << result->getDetails() << "\n";
                    } else {
                        cout << RED << "\n [X] No record found with ID '" << searchId << "'\n" << RESET;
                    }
                    break;
                }
                case 7: {
                    // Populate mock data
                    repo.add(make_shared<Student>("S01", "Alice Smith", 8.8));
                    repo.add(make_shared<Student>("S02", "Bob Johnson", 9.2));
                    repo.add(make_shared<Student>("S03", "Charlie Brown", 7.5));
                    repo.add(make_shared<Faculty>("F01", "Dr. Alan Turing", "Comp Sci"));
                    repo.add(make_shared<Faculty>("F02", "Marie Curie", "Physics"));
                    cout << GREEN << BOLD << "\n [v] Mock data loaded. Check Dashboard!\n" << RESET;
                    break;
                }
                case 8: {
                    repo.saveToFile("university_data.txt");
                    cout << GREEN << BOLD << "\n [v] Data successfully saved to 'university_data.txt'!\n" << RESET;
                    break;
                }
                case 9:
                    repo.saveToFile("university_data.txt");
                    cout << CYAN << BOLD << "\n Exiting University System. Goodbye!\n\n" << RESET;
                    break;

                default:
                    cout << RED << "\n [!] Invalid Choice. Please select a number between 1 and 9.\n" << RESET;
            }
        } 
        catch (const InvalidInputException& e) {
            cout << RED << "\n [ERROR] " << e.what() << RESET << "\n";
        } 
        catch (const exception& e) {
            cout << RED << "\n [SYSTEM ERROR] " << e.what() << RESET << "\n";
        }
    }
    
    return 0;
}
