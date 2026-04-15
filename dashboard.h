#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <vector>
#include <memory>
#include <string>
#include "models.h"

using namespace std;

extern const string RESET;
extern const string BOLD;
extern const string RED;
extern const string GREEN;
extern const string YELLOW;
extern const string BLUE;
extern const string CYAN;

void enableVirtualTerminal();

class Dashboard {
public:
    static void printHeader();
    static void printHeader(const string& subtitle);
    static void displayMenu();
    static void displayRecords(const vector<shared_ptr<Person>>& records, const string& filter = "All");
};

void clearInput();

#endif
