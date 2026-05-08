#pragma once
#include <fstream>
#include <sstream>
#include "DoubleList.h"
#include "Product.h"
#include "Client.h"
#include "Supplier.h"
using namespace std;

class FileManager {
public:

    // ─── PRODUCTOS ────────────────────────────────────────────────

    static void saveProducts(DoubleList<Product*>* products, string filename = "products.txt") {
        ofstream file(filename);
        if (!file.is_open()) { cout << "Error al abrir archivo." << endl; return; }
        Node<Product*>* current = products->head;
        while (current != nullptr) {
            Product* p = current->value;
            file << p->getId() << "," << p->getName() << ","
                << p->getCategory() << "," << p->getPrice()
                << "," << p->getStock() << "\n";
            current = current->next;
        }
        file.close();
        cout << "Productos guardados en " << filename << endl;
    }

    static void loadProducts(DoubleList<Product*>* products, string filename = "products.txt") {
        ifstream file(filename);
        if (!file.is_open()) { cout << "Archivo no encontrado: " << filename << endl; return; }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id, stock; string name, category; double price;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, token, ','); price = stod(token);
            getline(ss, token, ','); stock = stoi(token);
            products->addBack(new Product(id, name, category, price, stock));
        }
        file.close();
        cout << "Productos cargados desde " << filename << endl;
    }

    // ─── CLIENTES ─────────────────────────────────────────────────

    static void saveClients(DoubleList<Client*>* clients, string filename = "clients.txt") {
        ofstream file(filename);
        if (!file.is_open()) { cout << "Error al abrir archivo." << endl; return; }
        Node<Client*>* current = clients->head;
        while (current != nullptr) {
            Client* c = current->value;
            file << c->getId() << "," << c->getName() << ","
                << c->getEmail() << "," << c->getAddress()
                << "," << c->getMembership() << "\n";
            current = current->next;
        }
        file.close();
        cout << "Clientes guardados en " << filename << endl;
    }

    static void loadClients(DoubleList<Client*>* clients, string filename = "clients.txt") {
        ifstream file(filename);
        if (!file.is_open()) { cout << "Archivo no encontrado: " << filename << endl; return; }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id; string name, email, address, membership;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, address, ',');
            getline(ss, membership, ',');
            clients->addBack(new Client(id, name, email, "N/A", address, membership));
        }
        file.close();
        cout << "Clientes cargados desde " << filename << endl;
    }

    // ─── PROVEEDORES ──────────────────────────────────────────────

    static void saveSuppliers(DoubleList<Supplier*>* suppliers, string filename = "suppliers.txt") {
        ofstream file(filename);
        if (!file.is_open()) { cout << "Error al abrir archivo." << endl; return; }
        Node<Supplier*>* current = suppliers->head;
        while (current != nullptr) {
            Supplier* s = current->value;
            file << s->getId() << "," << s->getName() << ","
                << s->getEmail() << "," << s->getPhone()
                << "," << s->getCountry() << "," << s->getProductCategory() << "\n";
            current = current->next;
        }
        file.close();
        cout << "Proveedores guardados en " << filename << endl;
    }

    static void loadSuppliers(DoubleList<Supplier*>* suppliers, string filename = "suppliers.txt") {
        ifstream file(filename);
        if (!file.is_open()) { cout << "Archivo no encontrado: " << filename << endl; return; }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            int id; string name, email, phone, country, category;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, country, ',');
            getline(ss, category, ',');
            suppliers->addBack(new Supplier(id, name, email, phone, country, category));
        }
        file.close();
        cout << "Proveedores cargados desde " << filename << endl;
    }
};
