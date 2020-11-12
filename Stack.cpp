// Asuthor: Shaun Robinson
// Program: Stack 

#include<iostream>
using namespace std;

class Node {
private:
	int data;
public:
	Node* next;

	Node(int new_data = 0) : data(new_data), next(nullptr) {};
	int return_data() { return data; }
};

class Stack {
private:
	Node* top;
public:
	Stack() : top(nullptr) {};

	bool is_empty() { return top == nullptr; } // returns 1 or 0 if has data or not
	int peek() { return top->return_data(); }  // peeks at data does not change the stack return value of top
	void push(int new_data);                   // puts new data on top the the old data LIFO
	int pop();                                 // returns the data at the top of stack and sets top to next value
	
};

int main() {
	Stack s;
	int the_data, popped;

	// EXAMPLE
	cout << "This program shows how a stack works" << endl;
	for (int i = 0; i < 3; i++) {
		if (s.is_empty()) {
			cout << "The stack is empty please enter integers: " << endl;
		}
		cin >> the_data;
		s.push(the_data);
	}

	cout << "Peeking: " << endl;
	popped = s.peek();
	cout << popped << endl;
	popped = s.peek();
	cout << popped << endl;
	popped = s.peek();
	cout << popped << endl;
	popped = s.peek();
	cout << popped << endl << endl;

	cout << "Popping: " << endl;
	popped = s.pop();
	cout << popped << endl;
	popped = s.pop();
	cout << popped << endl;
	popped = s.pop();
	cout << popped << endl;
	popped = s.pop();
	cout << popped << endl;

	return 0;
}
void Stack::push(int new_data) {
	Node* new_top = new Node(new_data);

	if (top == NULL) {
		top = new_top;
		return;
	}

	Node* current = top;
	top = new_top;
	new_top->next = current;
}
int Stack::pop() {
	if (top == NULL) {
		return NULL;
	}

	Node* current = top;
	top = top->next;

	return current->return_data();
}