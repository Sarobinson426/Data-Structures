// Asuthor: Shaun Robinson
// Program: Queue

#include<iostream>
using namespace std;

class Node {
private:
	int data;
	
public:
	Node* previous;

	Node(int new_data = 0) : data(new_data), previous(NULL) {};

	int return_data() { return data; }
};

class Queue {
private:
	Node* front;
	Node* tail;
public:
	Queue() : front(NULL), tail(NULL) {};

	bool is_empty() { return front == NULL; }
	int peek() { return front->return_data(); }
	void add(int new_data);
	int remove();

};

int main() {
	Queue q;
	int the_data, the_peek;

	cout << "This program shows how a Queue works" << endl;
	// EXAMPLE
	for (int i = 0; i < 3; i++) {
		if (q.is_empty()) {
			cout << "Your queue is empty please enter integers (enter after each): ";
		}
		cin >> the_data;
		q.add(the_data);
	}
	cout << "Peeking: " << endl;
	the_peek = q.peek();
	cout << the_peek << endl;
	the_peek = q.peek();
	cout << the_peek << endl << endl;

	cout << "Removing: " << endl;
	the_peek = q.remove();
	cout << the_peek << endl;
	the_peek = q.remove();
	cout << the_peek << endl;
	the_peek = q.remove();
	cout << the_peek << endl;
	the_peek = q.remove();
	cout << the_peek << endl;

	return 0;
}

void Queue::add(int new_data) {
	Node* tail_node = new Node(new_data);  // adds new nodes from tail and updates tail pointer

	if (front == NULL) {
		front = tail_node;
		tail = tail_node;
		return;
	}

	tail->previous = tail_node;
	tail = tail_node;
}
int Queue::remove() {                      // removes data front return thats memory to heap and updates front to rest of list
	int data;

	if (front == NULL) {
		return NULL;
	}

	data = front->return_data();

	Node* new_front = front->previous;
	delete front;
	front = new_front;

	return data;
}