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

void Database::writeHashToFile(unsigned char* hash, int len) {
	write(hashFile, hash, len);
}

void Database::readHashFromFile() {
	// move file descriptor to the begining of the file before start reading
	lseek(hashFile, 0, SEEK_SET);
	// buffer to store reading hash
	unsigned char buff[32];
	// index
	int index = 1;
	// read one hash after another and print it in hexa format
	while(read(hashFile, buff, 32) == 32) {
		cout << index << "\t->\t";
		for (size_t i = 0; i < 32; i++) {
			printf("%02x ", buff[i]);
		}
		cout << endl; 
		index++;
	}
}
