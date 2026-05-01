#pragma once
#include <iostream>
#include "Client.h" 
#include "DoubleList.h"
#include "Stack.h"
#include "Product.h"

using namespace std;
class MenuClient {
private:
    Client* client;
    DoubleList<Product*>* products;  // lista de productos disponibles
    Stack<Product*>* cartHistory;    // historial del carrito con pila

public:
    MenuClient(Client* client, DoubleList<Product*>* products) {
        this->client = client;
        this->products = products;
        cartHistory = new Stack<Product*>();
    }

    void show() {
        int option;
        do {
            cout << "\n================================" << endl;
            cout << "#     BIENVENIDO, " << client->getName() << endl;
            cout << "#     AMAZONAS - CLIENTE        #" << endl;
            cout << "=================================" << endl;
            cout << "1. Ver productos" << endl;
            cout << "2. Buscar producto" << endl;
            cout << "3. Agregar al carrito" << endl;
            cout << "4. Ver historial del carrito" << endl;
            cout << "0. Cerrar sesion" << endl;
            cout << "Elige una opcion: "; cin >> option;
            system("cls");

            switch (option) {
            case 1:
                showProducts();
                break;
            case 2:
                searchProduct();
                break;
            case 3:
                addToCart();
                break;
            case 4:
                cartHistory->show();
                break;
            }
        } while (option != 0);
    }

private:
    void showProducts() {
        cout << "\n==== PRODUCTOS DISPONIBLES ====" << endl;
        // lambda para filtrar solo productos con stock
        auto hasStock = [](Product* p) {
            return p->getStock() > 0;
            };
        products->filter(hasStock);
    }

    void searchProduct() {
        string name;
        cout << "Ingrese nombre del producto: "; cin >> name;
        // lambda para buscar por nombre
        auto byName = [name](Product* p) {
            return p->getName() == name;
            };
        cout << "\n==== RESULTADO ====" << endl;
        products->filter(byName);
    }

    void addToCart() {
        int id;
        cout << "Ingrese ID del producto: "; cin >> id;
        Node<Product*>* current = products->head;
        while (current != nullptr) {
            if (current->value->getId() == id) {
                cartHistory->push(current->value);
                cout << "Producto agregado al carrito!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Producto no encontrado." << endl;
    }
};