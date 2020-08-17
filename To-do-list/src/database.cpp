#include "include/database.h"
#include <string.h>

vector<string> Database::readData() {
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

void Database::writeData(vector<string> list) {
	
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

void Database::writeHashToFile(unsigned char* hash) {
	write(hashFile, hash, strlen((const char*)hash));
	write(hashFile, "\n", 2);
}
