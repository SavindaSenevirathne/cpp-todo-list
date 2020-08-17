#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Database
{
    private:
        /* data */
    public:
        void write(vector<string> list);
        vector<string> read();
};

