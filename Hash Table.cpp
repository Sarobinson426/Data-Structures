// Asuthor: Shaun Robinson
// Program: Hash Table 

#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

static const int TABLE = 10;          // size can be changed. Use static so use variable to set static array
static const int DRINKS = 4;          // static array can't have variables so use static const

class Item {                          // stores name, drink, next and previous for linked list 
private:                                  
	string name;
	string drink[DRINKS];             // drinks  are limited to three but can increase use static const 
public:
	Item* next;                       // cycles to next customer/name
	Item* previous;                   // cycles backwards if functionality is needed (not used here)

	Item(string new_name) : name(new_name), next(NULL), previous(NULL) {  // constructor used to set new items and append to lists
		for (int i = 0; i < DRINKS - 1; i++) {                            
			drink[i] = "empty";
		}
		drink[3] = "No more drinks!";
	};
	
	string return_name() { return name; }        // used to retrieve name from hash_table
	string return_drink() { return drink[0]; }   // used to return first drink from hash_table
	void cycle_through_drinks(string add_drink); // adds drinks to the next "empty" drink element in array
	void print_all_drinks();                     // prints all non-empty drinks elements accessible from hash_table
};

class Hash {
private:
	static const int table_size = TABLE;
	Item* start;
	Item* hash_table[table_size];
public:
	Hash() : start(NULL) {                      // initialize the hash_table to name = "empty"and null 
		for (int i = 0; i < table_size; i++) {
			hash_table[i] = new Item("empty");
		}
	};
 	int hash_index(string key);                       // finds the hash index. Where to store Item
	void add_item(string new_name, string new_drink); // adds a new item input from user on name and drink
	int number_of_items(string name_to_find);         // counts number of items by name
	int number_of_items(int index);                   // counts number of items by index
	void print();                                     // prints all the items in the hash_table 
};

int main() {
	Hash h;
	string input_name, input_drink;
	cout << "This is a hash table that store a person's name and up to three favorite drinks" << endl;
	cout << "This example will allow user to input name drink and will add preprogrammed names and drinks" << endl << endl;

	// EXAMPLE USE EXAMPLE
	cout << "Enter information" << endl;
	for (int i = 0; i < 1; i++) {
		cout << "first name only: ";
		cin >> input_name;
		cout << "\nsingle drink: ";
		cin >> input_drink;
		h.add_item(input_name, input_drink);
	}

	h.add_item("Starbucks", "latte");
	cout << "***********Adding examples to hash_table**************" << endl;
	cout << "y/n to add customer or drink to existing customer" << endl;
	h.add_item("Starbucks", "pumpkin spice latte");
	cout << "***********Adding examples to hash_table**************" << endl;
	cout << "y/n to add customer or drink to existing customer" << endl;
	h.add_item("Starbucks", "cafe con leche");
	h.print();

	return 0;
}
void Item::cycle_through_drinks(string add_drink) {
	int i;

	i = 0;
	while (i != DRINKS - 1) {
		if (i >= 3) {
			return;
		}
		else if (drink[i] == "empty") {
			drink[i] = add_drink;
			break;
		}
		i++;
	}
	return;
}
void Item::print_all_drinks() {
	int i;

	i = 0;
	while (drink[i] != "empty" && i < 3) {
		cout << drink[i];
		if (i < 3) {
			cout << ", ";
		}
		i++;
	}
}
//will determine the location in hash table with % table size
int Hash::hash_index(string key) {
	int hash = 0;

	for (string::iterator it = key.begin(); it != key.end(); it++) {
		hash += static_cast<int>(*it);
	}

	hash %= table_size;

	return hash;
}
// adds entry to the hash table
void Hash::add_item(string new_name, string new_drink) {
	int index = hash_index(new_name);
	char yes_no;
	Item* new_item = new Item(new_name);

	if (hash_table[index]->return_name() == "empty") {
		new_item->cycle_through_drinks(new_drink);
		hash_table[index] = new_item;
		start = hash_table[index];
	}
	else if (hash_table[index]->return_name() == new_name) {
		cout << "Name already exists would you like to add another drink(y/n)? ";
		cin >> yes_no;
		while (static_cast<int>(yes_no) > 121 || static_cast<int>(yes_no) < 110 || (static_cast<int>(yes_no) > 110 && static_cast<int>(yes_no) < 121)) {
			cout << "Incorrect. Please answer with 'y' for yes or 'n' for no: ";
			cin >> yes_no;
		}
		if (yes_no == 'y') {
			hash_table[index]->cycle_through_drinks(new_drink);
		}
		else {
			cout << "Would you like to add another entry (y/n)? ";
			cin >> yes_no;
			while (static_cast<int>(yes_no) > 121 || static_cast<int>(yes_no) < 110 || (static_cast<int>(yes_no) > 110 && static_cast<int>(yes_no) < 121)) {
				cout << "Incorrect. Please answer with 'y' for yes or 'n' for no: ";
				cin >> yes_no;
			}
			if (yes_no == 'y') {
				Item* current = hash_table[index];

				while (current->next != NULL) {
					current = current->next;
				}

				new_item->cycle_through_drinks(new_drink);
				current->next = new_item;
				new_item->previous = current;
			}
		}
	}
}
int Hash::number_of_items(string name_to_find) {
	int count = 0, index;

	index = hash_index(name_to_find);
	if (name_to_find == "empty") {
		return count;
	}
	else if (hash_table[index]->return_name() == name_to_find) {
		Item* current = hash_table[index];

		while (current != NULL) {
			count++;
			current = current->next;
		}
	}
	return count;
}
int Hash::number_of_items(int index) {
	Item* current = hash_table[index];
	int count;
	
	count = 0;
	if (hash_table[index]->return_name() == "empty") {
		return count;
	}
	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}
void Hash::print() {
	int num;

	for (int i = 0; i < table_size; i++) {
		num = number_of_items(i);

		cout << "-----------------------------------" << endl;
		cout << "Index: " << i << endl;
		if (num > 1) {
			Item* current = hash_table[i];

			while (hash_table[i] != NULL) {
				cout << "Name: " << hash_table[i]->return_name() << endl;
				cout << "Drinks: ";
				hash_table[i]->print_all_drinks();
				hash_table[i] = hash_table[i]->next;
				cout << endl;
			}
			cout << endl;
			hash_table[i] = current;
		} 
		else {
			cout << "Name: " << hash_table[i]->return_name() << endl;
			cout << "Drinks: ";
			hash_table[i]->print_all_drinks();
			cout << endl;
		}
		cout << "Number of items: " << num << endl;
		cout << "-----------------------------------" << endl;
	}
}