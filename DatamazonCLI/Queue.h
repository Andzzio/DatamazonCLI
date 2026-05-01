
#pragma once
#include "Node.h"
using namespace std;
template<typename T>
class Stack
{
private:
	Node<T>* top;

public:
	Stack() {
		top == nullptr;
	}

	void push(T value) {
		Node<T>* newNode = new Node<T>(value);
		newNode->next = top;
		top = newNode;
	}
	void pop() {

		if (top == nullptr) {
			cout << "Stack vacio" << endl;
			return;
		}
		Node<T>* temp = top;
		top = temp->next;
		delete temp;
	}
	T peek() {
		if (top == nullptr) {
			cout << "Stack vacio...";
			return;
		}
		return top->value;
	}

	bool isEmpty() {
		return top == nullptr;
	}

	void show() {
		Node<T>* current = top;
		cout << "Tope" << endl;
		while (current != nullptr)
		{
			cout << "[" << current->value << "]" << endl;
			current = current->next;
		}
		cout << "BOTTON" << endl;
	}


	~Stack() {}



};