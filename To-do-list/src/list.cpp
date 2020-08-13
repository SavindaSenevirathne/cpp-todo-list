#include "include/list.h"
#include <sodium.h>

void List::print_menu() {
	cout << "\n\n\n*******************" << endl;
	cout << "1. Print all" << endl;
	cout << "2. Add an item" << endl;
	cout << "3. Delete an item by index" << endl;
	cout << "4. Hash of all using libsodium" << endl;
	cout << "5. Exit program" << endl;
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
			calc_hash_for_all();
			break;
		case 5:
			exit(0);    
		default:
			cout << "Invalid choice.. Try again" << endl;
			print_menu();
			break;
	}
}

void List::add_item() {
	cout << "Add an item: ";
	string item;
	// ignore the newline character from menu choosing
	cin.ignore(1000, '\n');
	std::getline (std::cin,item);
	cout << item << endl;
	list.push_back(item);
	cin.clear();
}

void List::print_all() {
	if (list.size() > 0) {
		for (int i = 0; i < (int)list.size(); i++)
		{
			cout << i + 1 << ". " << list[i] << endl;
		}
		cout << endl;
	}
}

void List::delete_item() {
	if (list.size() > 0) {
		print_all();
		cout << "Enter item to delete: ";
		int index;
		cin >> index;
		cin.clear();
		list.erase(list.begin() + index - 1);
	}
}

void List::calc_hash_for_all() {
	for (int i = 0; i < (int)list.size(); i++) {
		// variable to store generated hash
		unsigned char hash[crypto_generichash_BYTES];
		// generate hash and store in hash variable
		crypto_generichash(hash, sizeof hash, ((const unsigned char *)list[i].c_str()), sizeof list[i], NULL, 0);
		// print current todo item
		cout << i + 1 << ". " << list[i] << " - ";
		// Print the hash in hexadecimal
		for(int j = 0; j < (int)crypto_generichash_BYTES; j++)
		{
			// output a minimum of 2 hex digits
			printf("%02x ", hash[j]);
		}
		cout << endl;

	}
}