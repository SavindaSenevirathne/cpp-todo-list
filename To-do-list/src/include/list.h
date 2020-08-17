#include <iostream>
#include <vector>
#include <sodium.h>
#include <blake3.h>
#include "database.h"

using namespace std;

class List
{
    private:
        /* data */

    public:
        string name;
        vector<string> list;
        Database db;
        void print_menu();
        void add_item();
        void print_all();
        void delete_item();
        void calc_hash_for_all(bool printOnTerminal);
        void calc_hash_Blake3(bool printOnTerminal);
        void benchmark();
};


