#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template<typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* back;

public:
    Queue() { front = back = nullptr; }

    // ─── MÉTODOS ORIGINALES ───────────────────────────────────────

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (back == nullptr) { front = back = newNode; return; }
        back->next = newNode;
        back = newNode;
    }

    void dequeue() {
        if (front == nullptr) { cout << "No hay pedidos en cola." << endl; return; }
        Node<T>* temp = front;
        front = front->next;
        if (front == nullptr) back = nullptr;
        delete temp;
    }

    T peek() {
        if (front == nullptr) { cout << "No hay pedidos en cola." << endl; return T(); }
        return front->value;
    }

    bool isEmpty() { return front == nullptr; }

    void showAll() {
        if (front == nullptr) { cout << "No hay pedidos en cola." << endl; return; }
        Node<T>* current = front;
        int pos = 1;
        cout << "\n==== COLA DE PEDIDOS ====" << endl;
        while (current != nullptr) {
            cout << "Posicion #" << pos++ << ":" << endl;
            current->value->show();
            current = current->next;
        }
    }

    int count() {
        int total = 0;
        Node<T>* current = front;
        while (current != nullptr) { total++; current = current->next; }
        return total;
    }

    // ─── MÉTODOS NUEVOS ───────────────────────────────────────────

    // 1. countRecursive(node) — cuenta pedidos recursivamente — O(n)
    int countRecursive(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countRecursive(node->next);
    }

    // 2. contains(id) — verifica si un pedido está en la cola — O(n)
    bool contains(int id) {
        Node<T>* current = front;
        while (current != nullptr) {
            if (current->value->getId() == id) return true;
            current = current->next;
        }
        return false;
    }

    // 3. getTotalRevenue() — suma los totales de todos los pedidos — O(n)
    double getTotalRevenue() {
        double total = 0;
        Node<T>* current = front;
        while (current != nullptr) {
            total += current->value->getTotal();
            current = current->next;
        }
        return total;
    }

    // 4. filterByStatus(status) — muestra pedidos por estado — O(n) con lambda
    template<typename Funcion>
    void filter(Funcion condition) {
        Node<T>* current = front;
        while (current != nullptr) {
            if (condition(current->value)) current->value->show();
            current = current->next;
        }
    }

    // 5. clearAll() — vacia toda la cola — O(n)
    void clearAll() {
        while (!isEmpty()) dequeue();
        cout << "Cola vaciada." << endl;
    }

    ~Queue() {}
};
