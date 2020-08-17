#include <iostream>
#include <fstream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Database
{
    private:
        /* data */
        int hashFile;
    public:
        Database() {
            hashFile = open("data/hash", O_WRONLY);
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
        void writeHashToFile(unsigned char*);
};

