// Author: Shaun Robinson
// Program: Double Linked List

#include<iostream>
#include<ctime>
using namespace std;

class Node { // what constitutes the contents of each node
private:
	int data; // this linked list has just one value data 
	          // but could have multiple types of values
public:
	Node* next;      // pointer to next node
	Node* previous;  // ponter to prevoius node

	Node(int new_data = 0) : data(new_data), next(nullptr), previous(nullptr) {};  // constructor
	Node(const Node*& new_node) {
		*this = new_node;
	}
	int return_data() { return data; } // method to return data in the current node (in line)
};

class LinkedList {
private:
	Node* head;  // pointer to keep track of the beginning of the list 
	Node* tail;  // pointer to keep track of the end of the list

public:
	LinkedList() : head(NULL), tail(NULL) {};
	void append(int new_data);               // adds new node at tail
	void prepend(int new_data);              // adds new node at head
	void insert(int new_data, int insert_after); //inserts after a value specified by programmer
	void delete_nodes(int delete_data);      // deletes all nodes of data value 
	void delete_a_node(int delete_data);     // deletes single node of data value
	void print_fwd(ostream& outs);           // prints linked list forwards from head to tail
	void print_rev(ostream& outs);           // prints linked list in reverse from tail to head

};

int main() {
	LinkedList the_list;
	int input, delete_input;

	cout << "This program demonstrates a doubly linked list" << endl;
	cout << "Enter numbers into your linked list: ";
	for (int i = 0; i < 3; i++) {                    // example of how to use
		cin >> input;
		the_list.append(input);
	}
	for (int i = 0; i < 3; i++) {
		cin >> input;
		the_list.prepend(input);
	}
	
	// e.g. 
	the_list.print_fwd(cout);
	cout << endl;
	the_list.print_rev(cout);
	cout << endl;

	cout << "Enter a number to delete: " << endl;
	cin >> delete_input;
	
	the_list.delete_a_node(delete_input);
	the_list.insert(15, 22);
	the_list.print_fwd(cout);
	cout << endl;
	the_list.print_rev(cout);

	return 0;
}
void LinkedList::append(int new_data) {
	Node* new_node = new Node(new_data);

	if (head == NULL || tail == NULL) { // if head does not have value new_node is the head and tail
		head = new_node;                // NULL in this condition means no values in list yet
		tail = new_node;
		return;
	}

	Node* current = tail;       // current is used to transverse the list so tail position/value is not changed

	current->next = new_node;   // sets a new node after current node (appends a value to list)
	new_node->previous = current; // links the new node to current 
	tail = new_node;            // sets the tail to the appended value
}
void LinkedList::prepend(int new_data) {
	Node* new_node = new Node(new_data);

	if (head == NULL || tail == NULL) {
		head = new_node;                // no nodes yet sets new node as both head and tail
		tail = new_node;
		return;
	}

	Node* current = head;               // sets current to value of head so can transverse list without changing head value/position

	current->previous = new_node;       // prepends value to the head of list (adds to beginning new beginning)
	new_node->next = current;           // new node next pointer points to what will be old head
	head = new_node;                    // head value is set to the new beginning of the list
}
void LinkedList::insert(int new_data, int insert_after) {
	Node* new_node = new Node(new_data); // "captures" new_data into a node
	Node* current = head;                // current is set to head so value of head is preserved
	
	while (current != NULL) {            // transverse list starting at head
		if (current->return_data() == insert_after) { // evaluates if currents value is the node we want to insert after
			if (current->next == NULL) { // if the next value is null this means we are at end of list and new_node will be new tail 
				tail = new_node;         // assign tail to new_node value (tail pointer now points to new_node)
			}
			new_node->previous = current; // sets the new_nodes pointers 
			new_node->next = current->next;
			current->next = new_node;
			return;
		}
		else {
			current = current->next;
		}
	}
}
void LinkedList::delete_a_node(int delete_data) {
	Node* current = head;

	if (head == NULL) {
		return;
	}
	if (current->return_data() == delete_data && current->next == NULL) { 
		head = NULL;
		tail = NULL;
		return;
	}

	while (current != NULL) {
		if (current->return_data() == delete_data) {  // checks if value of node is the value we want to remove
			if (current->previous == NULL) {
				current->next->previous == NULL;      // sets pointers if head of list
				head = current;                       // new head because old head is now going to be deleted
				delete current;					      // returns memory to heap
				//current = NULL;                       // "erases" value just sets to null (alt)
				return;                        
			}
			else {
				current->next->previous = current->previous;
				current->previous->next = current->next;
				current = NULL;
				return;
			}
		}
		else {
			current = current->next;
		}
	}
}
void LinkedList::delete_nodes(int delete_data) {

	if (head == NULL) {
		return;
	}
	else if (head->return_data() == delete_data && head->next == NULL) {
		head = NULL;
		return;
	}

	Node* current = head;

	while (current != NULL) {
		if (current->return_data() == delete_data) {
			current->next->previous = current->previous;
			current->previous->next = current->next;
			
			Node* next_current = current->next;
			current = NULL;
			current = next_current;
		}
		else {
			current = current->next;
		}
	}
}
void LinkedList::print_fwd(ostream& outs) {
	Node* current = head;

	while (current != NULL) {
		cout << current->return_data() << " ";
		current = current->next;
	}
}

void LinkedList::print_rev(ostream& outs) {
	Node* current = tail;
	
	while (current != NULL) {
		cout << current->return_data() << " ";
		current = current->previous;
	}
}