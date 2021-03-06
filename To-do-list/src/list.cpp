#include "include/list.h"
#include <chrono>  // for high_resolution_clock

void List::print_menu() {
	cout << "\n\n\n*******************" << endl;
	cout << "1. Print all" << endl;
	cout << "2. Add an item" << endl;
	cout << "3. Delete an item by index" << endl;
	cout << "4. Hash of all using libsodium" << endl;
	cout << "5. Hash of all using Blake 3" << endl;
	cout << "6. Read from file" << endl;
	cout << "7. Write to the file" << endl;
	cout << "8. Benchmark" << endl;
	cout << "9. Read hash for Blake3 from file" << endl;
	cout << "10. Exit program" << endl;
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
			calc_hash_for_all(true);
			break;
		case 5:
			calc_hash_Blake3(true);
			break;
		case 6:
			list = db.readData();
			break;
		case 7:
			db.writeData(list);
			break;
		case 8:
			benchmark();    
			break;
		case 9:
			db.readHashFromFile();    
			break;
		case 10:
			exit(0);    
			break;
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

double List::calc_hash_for_all(bool printOnTerminal) {
	// remove the content in the file from the previous run
	ftruncate(db.hashFile, 0);
	// start function execution
    auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < (int)list.size(); i++) {
		// variable to store generated hash
		unsigned char hash[crypto_generichash_BYTES];
		// generate hash and store in hash variable
		crypto_generichash(hash, sizeof hash, ((const unsigned char *)list[i].c_str()), sizeof list[i], NULL, 0);
		// print current todo item
		if (printOnTerminal) {
			cout << i + 1 << ". " << list[i] << " - ";
			// Print the hash in hexadecimal
			for(int j = 0; j < (int)crypto_generichash_BYTES; j++)
			{
				// output a minimum of 2 hex digits
				printf("%02x ", hash[j]);
			}
			cout << endl;
			// write hashes to the binary file
			db.writeHashToFile(hash, crypto_generichash_BYTES);
		}

	}
	auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
	if (printOnTerminal) {
    	cout << "Elapsed time for Blake2b: " << elapsed.count() << " s" << endl;
	}
	return elapsed.count();

}

double List::calc_hash_Blake3(bool printOnTerminal) {
	// remove the content in the file from the previous run
	ftruncate(db.hashFile, 0);
    auto start = std::chrono::high_resolution_clock::now(); 
	for (int i = 0; i < (int)list.size(); i++) {
		
		// Initialize the hasher.
		blake3_hasher hasher;
		blake3_hasher_init(&hasher);
		blake3_hasher_update(&hasher, list[i].c_str(), sizeof list[i]);

		uint8_t output[BLAKE3_OUT_LEN];
		blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);
		if (printOnTerminal) {
			// print current todo item
			cout << i + 1 << ". " << list[i] << " - ";
			// Print the hash as hexadecimal.
			for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) {
				printf("%02x ", output[i]);
			}
			printf("\n");
			// write hashes to the binary file
			db.writeHashToFile(output, BLAKE3_OUT_LEN);
		}

	}
	auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
	if (printOnTerminal) {
    	cout << "Elapsed time for Blake3: " << elapsed.count() << " s" << endl;
	}
	return elapsed.count();
}

void List::benchmark() {
	cout << "Benchmark using " << list.size() << " list items" << endl;
	double blake2TotalTime = 0;
	double blake3TotalTime = 0;

	for (int i = 0; i < 10; i++) {
		blake2TotalTime += calc_hash_for_all(false);
		blake3TotalTime += calc_hash_Blake3(false);
	}
	cout << "Blake2b average time for 10 runs: " << (blake2TotalTime / 10) << " s" << endl; 
	cout << "Blake3 average time for 10 runs: " << (blake3TotalTime / 10) << " s" << endl; 
}
