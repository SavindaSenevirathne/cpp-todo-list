#include <iostream>
#include <vector>

using namespace std;

class List
{
    private:
        /* data */

    public:
        string name;
        vector<string> list;
        void print_menu();
        void add_item();
        void print_all();
        void delete_item();
        void calc_hash_for_all();
};


