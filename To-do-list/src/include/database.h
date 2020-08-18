#include <iostream>
#include <fstream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Database
{
    private:
    public:
        /* data */
        int hashFile;
        Database() {
            // create new file if it is not already exists
            hashFile = open("data/hash", O_RDWR | O_CREAT);
            if (hashFile == -1) {
                cout << "Opening file failed." << endl;
                exit(-1);
            }
        }
        ~Database() {
            close(hashFile);
        }
        void writeData(vector<string> list);
        vector<string> readData();
        void writeHashToFile(unsigned char*, int);
        void readHashFromFile();
};

