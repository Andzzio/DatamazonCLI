#pragma once
#include"Node.h"
template<typename T>
class DoubleList
{
public:
	Node<T>* head;
	Node<T>* tail;

	DoubleList() {
		head = tail = nullptr;
	}
	void addBack(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (tail == nullptr) {
			tail = newNode;
			head = newNode;
			return;
		}
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
	}
	void addFront(T value) {

		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			return;
		}
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
	void showFrontToBack() {
		if (head == nullptr) { 
			cout << "Lista vacia." << endl;
			return;
		}
		Node<T>* current = head;
		while (current != nullptr) {
			current->value->show();
			current = current->next;
		}
	}
	template<typename Funcion>
	void filter(Funcion condition) {
		Node<T>* current = head;
		while (current != nullptr) {
			if (condition(current->value)) {
				current->value->show();
			}
			current = current->next;
		}
	}
	void deleteById(int id) {
		if (head == nullptr) { 
			cout << "Lista vacia." << endl; return; 
		}
		if (head->value->getId() == id) {
			Node<T>* temp = head;
			head = head->next;
			if (head != nullptr) {
				head->previous = nullptr;
			}
			else {
				tail = nullptr;
			}
			delete temp;
			return;
		}

		Node<T>* current = head;
		while (current->next != nullptr) {
			if (current->next->value->getId() == id) {
				Node<T>* temp = current->next;
				current->next = temp->next;
				if (temp->next != nullptr) {
					temp->next->previous = current;
				}
				else {
					tail = current;
				}
				delete temp;
				return;
			}
			current = current->next;
		}
		cout << "Producto no encontrado." << endl;
	}


};