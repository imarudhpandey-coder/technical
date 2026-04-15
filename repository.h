#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "models.h"

using namespace std;

template <typename T>
class Repository {
private:
    vector<shared_ptr<T>> items;
public:
    void add(shared_ptr<T> item) {
        items.push_back(item);
    }

    const vector<shared_ptr<T>>& getAll() const {
        return items;
    }

    shared_ptr<T> findById(const string& id) {
        for (auto& item : items) {
            if (item->getId() == id) return item;
        }
        return nullptr;
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "\n [ERROR] Could not open file for writing: " << filename << "\n";
            return;
        }
        for (const auto& item : items) {
            outFile << item->toCSV() << "\n";
        }
        outFile.close();
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) return; 
        
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type, id, name, extra;
            getline(ss, type, ',');
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, extra, ',');
            
            if (type == "Student") {
                add(make_shared<Student>(id, name, stof(extra)));
            } else if (type == "Faculty") {
                add(make_shared<Faculty>(id, name, extra));
            }
        }
        inFile.close();
    }
};

#endif
