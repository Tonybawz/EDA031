#include <iostream>
#include "list.h"

List::List() {
	first = nullptr;
}

List::~List() {
	Node *node;
	node = first;
	while (node != nullptr){
		struct Node *deletenode;
		deletenode = node;
		node = node->next;
		delete deletenode;
	}
	first = nullptr;
}

bool List::exists(int d) const {
	Node *node;
	node = first;
	while (node != nullptr){
		if (node->value == d){
			return true;
		}
		node = node->next;
	}
	return false;
}

int List::size() const {
	int counter = 0;
	struct Node *node;
	node = first;
	while (node != nullptr){
		counter++;
		node = node->next;
	}
	return counter;
}

bool List::empty() const {
	return first == nullptr;
}

void List::insertFirst(int d) {
	struct Node *node = new struct Node(d, first);
	first = node;
}

void List::remove(int d, DeleteFlag df) {
	struct Node *current, *prev, *temp;
	current = first;
	prev = first;
	bool done = false;
	while (!done && current != nullptr){
		bool envokedelete = false;

		if (df == List::DeleteFlag::LESS && current->value < d){
			envokedelete = true;
		}
		else if (df == List::DeleteFlag::EQUAL && current->value == d){
			envokedelete = true;
		}
		else if (df == List::DeleteFlag::GREATER && current->value > d){
			envokedelete = true;
		}
		else {
			prev = current;
			current = current->next;
		}
		if (envokedelete == true){
			if (current == first){
				first = current->next;
				delete current;
			}
			else {
				temp = current;
				prev->next = current->next;
				current = current->next;
				delete temp;
			}
			done = true;
		}

	}
}

void List::print() const {
	struct Node * node;
	node = first;
	while (node != nullptr) {
		std::cout << node->value << std::endl;
		node = node->next;
	}
}

