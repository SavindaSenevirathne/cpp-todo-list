#include "include/database.h"

vector<string> Database::read() {
    vector<string> list;
    
    ifstream database;
    database.open("data/db.txt");
    if (database.is_open()) {
        string currentLine;
        while (getline(database, currentLine, '\n')) {
            list.push_back(currentLine);
        }
        cout << "Successfully added " << (int)list.size() << " items" << endl;
    } else {
        cout << "Error reading file" << endl;
    }
    database.close();
    return list;
}

void Database::write(vector<string> list) {
    
    ofstream database;
    database.open("data/db.txt");

    if (database.is_open()) {
        for (int i = 0; i < (int)list.size(); i++) {
            database << list[i] << endl;
        }
        cout << "Successfully saved " << (int)list.size() << " items" << endl;

    } else {
        cout << "Error writing to file" << endl;
    }

    database.close();
}