#pragma once
#include "Node.h"
template<typename T>
class DoubleList
{
public:
    Node<T>* head;
    Node<T>* tail;

    DoubleList() {
        head = tail = nullptr;
    }

    // ─── MÉTODOS ORIGINALES ───────────────────────────────────────

    void addBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) { tail = head = newNode; return; }
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void addFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) { head = tail = newNode; return; }
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    void showFrontToBack() {
        if (head == nullptr) { cout << "Lista vacia." << endl; return; }
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
            if (condition(current->value)) current->value->show();
            current = current->next;
        }
    }

    void deleteById(int id) {
        if (head == nullptr) { cout << "Lista vacia." << endl; return; }
        if (head->value->getId() == id) {
            Node<T>* temp = head;
            head = head->next;
            if (head != nullptr) head->previous = nullptr;
            else tail = nullptr;
            delete temp;
            return;
        }
        Node<T>* current = head;
        while (current->next != nullptr) {
            if (current->next->value->getId() == id) {
                Node<T>* temp = current->next;
                current->next = temp->next;
                if (temp->next != nullptr) temp->next->previous = current;
                else tail = current;
                delete temp;
                return;
            }
            current = current->next;
        }
        cout << "Elemento no encontrado." << endl;
    }

    // ─── MÉTODOS NUEVOS ───────────────────────────────────────────

    // 1. count() — cuenta cuántos nodos hay — O(n)
    int count() {
        int total = 0;
        Node<T>* current = head;
        while (current != nullptr) { total++; current = current->next; }
        return total;
    }

    // 2. contains(id) — verifica si existe un elemento con ese id — O(n)
    bool contains(int id) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value->getId() == id) return true;
            current = current->next;
        }
        return false;
    }

    // 3. getById(id) — retorna el elemento con ese id — O(n)
    T getById(int id) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value->getId() == id) return current->value;
            current = current->next;
        }
        return nullptr;
    }

    // 4. showBackToFront() — muestra la lista al revés — O(n)
    void showBackToFront() {
        if (tail == nullptr) { cout << "Lista vacia." << endl; return; }
        Node<T>* current = tail;
        cout << "=== LISTA INVERSA ===" << endl;
        while (current != nullptr) {
            current->value->show();
            current = current->previous;
        }
    }

    // 5. sortByPrice() — Bubble Sort por precio ascendente — O(n²)
    void sortByPrice() {
        if (head == nullptr) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head;
            while (current->next != nullptr) {
                if (current->value->getPrice() > current->next->value->getPrice()) {
                    T temp = current->value;
                    current->value = current->next->value;
                    current->next->value = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Productos ordenados por precio (menor a mayor)." << endl;
    }

    // 6. sortByName() — Bubble Sort por nombre ascendente — O(n²)
    void sortByName() {
        if (head == nullptr) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head;
            while (current->next != nullptr) {
                if (current->value->getName() > current->next->value->getName()) {
                    T temp = current->value;
                    current->value = current->next->value;
                    current->next->value = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Lista ordenada alfabeticamente." << endl;
    }

    // 7. mergeSort() — Merge Sort recursivo por precio — O(n log n)
    void mergeSort() {
        head = mergeSortHelper(head);
        // recalcular tail
        Node<T>* current = head;
        while (current && current->next) current = current->next;
        tail = current;
        cout << "Productos ordenados con Merge Sort (precio asc)." << endl;
    }

    // 8. countRecursive(node) — cuenta nodos de forma recursiva — O(n)
    int countRecursive(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countRecursive(node->next);
    }

    // 9. searchRecursive(node, id) — busca un nodo recursivamente — O(n)
    T searchRecursive(Node<T>* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->value->getId() == id) return node->value;
        return searchRecursive(node->next, id);
    }

private:
    // ─── HELPERS PARA MERGE SORT ─────────────────────────────────

    Node<T>* mergeSortHelper(Node<T>* node) {
        if (node == nullptr || node->next == nullptr) return node;
        Node<T>* mid = getMiddle(node);
        Node<T>* half = mid->next;
        mid->next = nullptr;
        if (half) half->previous = nullptr;
        Node<T>* left = mergeSortHelper(node);
        Node<T>* right = mergeSortHelper(half);
        return merge(left, right);
    }

    Node<T>* getMiddle(Node<T>* node) {
        Node<T>* slow = node;
        Node<T>* fast = node->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node<T>* merge(Node<T>* a, Node<T>* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->value->getPrice() <= b->value->getPrice()) {
            a->next = merge(a->next, b);
            if (a->next) a->next->previous = a;
            a->previous = nullptr;
            return a;
        }
        else {
            b->next = merge(a, b->next);
            if (b->next) b->next->previous = b;
            b->previous = nullptr;
            return b;
        }
    }
};
