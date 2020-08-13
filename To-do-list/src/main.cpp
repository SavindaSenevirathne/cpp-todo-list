#include "include/list.h"

int main(int argc, char* args[]) {
    List list;
    if (argc > 1) {
        list.name = args[1];
        cout << list.name << endl;
    } else {
        cout << "You can enter the name as a command line argument\n";
    }
    while(1) {
        list.print_menu();
    }

    return 0; 
}
