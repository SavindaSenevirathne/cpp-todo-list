#include <iostream>
#include <vector>
using namespace std;

void print_menu();
void add_item();
void print_all();
void delete_item();

string name;
vector<string> list;

int main(int argc, char* args[]) {
    if (argc > 1) {
        name = args[1];
        cout << name << endl;
        while(1) {
            print_menu();
        }
    } else {
        cout << "You can enter the name as a command line argument\n";
        print_menu();

    }

    return 0; 
}

void print_menu() {
    cout << "*******************" << endl;
    cout << "1. Print all" << endl;
    cout << "2. Add an item" << endl;
    cout << "3. Delete an item by index" << endl;
    cout << "4. Exit program" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    // clearing input buffer
    cin.clear();

    switch (choice)
    {
        case 1:
            print_all();
            break;
        case 2:
            add_item();
            break;
        case 3:
            delete_item();
            break;
        case 4:
            exit(0);    
        default:
            cout << "Invalid choice.. Try again" << endl;
            print_menu();
            break;
    }
}

void add_item() {
    cout << "Add an item: ";
    string item;
    cin >> item;
    list.push_back(item);
    cin.clear();
}

void print_all() {
    if (list.size() > 0) {
        for (int i = 0; i < list.size(); i++)
        {
            cout << i << ". " << list[i] << endl;
        }
        cout << endl;
    }
}

void delete_item() {
    if (list.size() > 0) {
        print_all();
        cout << "Enter index to delete: ";
        int index;
        cin >> index;
        cin.clear();
        list.erase(list.begin() + index);
    }
}