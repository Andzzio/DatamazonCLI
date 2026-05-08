#pragma once
#include "Entity.h"
#include "DoubleList.h"
#include "Product.h"
#include "Queue.h"    
#include "Order.h"      
#include "Supplier.h"   
#include <iostream>     
#include <string>  

class MenuAdmin
{
private:
    DoubleList<Product*>* products;
    Queue<Order*>* orderQueue;
    DoubleList<Supplier*>* suppliers;
public:
    MenuAdmin(DoubleList<Product*>* products, Queue<Order*>* orderQueue, DoubleList<Supplier*>* suppliers) {
        this->products = products;
        this->orderQueue = orderQueue;
        this->suppliers = suppliers;
    }
    void show() {
        int option;
        do {
            cout << "\n==============================" << endl;
            cout << "=   AMAZONIA - ADMINISTRADOR   =" << endl;
            cout << "===============================" << endl;
            cout << "1. Ver todos los productos" << endl;
            cout << "2. Agregar producto" << endl;
            cout << "3. Eliminar producto" << endl;
            cout << "4. Filtrar por categoria" << endl;
            cout << "5. Filtrar por precio maximo" << endl;
            cout << "6. Ver cola de pedidos" << endl;
            cout << "7. Procesar siguiente pedido" << endl;
            cout << "8. Ver proveedores" << endl;
            cout << "9. Agregar proveedor" << endl;
            cout << "10. Buscar proveedor por categoria" << endl;
            cout << "0. Cerrar sesion" << endl;
            cout << "Elige una opcion: "; cin >> option;
            system("cls");

            switch (option) {
            case 1:
                products->showFrontToBack();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                filterByCategory();
                break;
            case 5:
                filterByPrice();
                break;
            case 6:
                orderQueue->showAll();
                break;
            case 7:
                processNextOrder();
                break;
            case 8:
                suppliers->showFrontToBack();
                break;
            case 9:
                addSupplier();
                break;
            case 10:
                filterSupplierByCategory();
                break;
            }
        } while (option != 0);
    }
    void addSupplier() {
        int id;
        string name, email, phone, country, category;
        cout << "==== NUEVO PROVEEDOR ====" << endl;
        cout << "ID: ";        cin >> id;
        cout << "Nombre: ";    cin >> name;
        cout << "Email: ";     cin >> email;
        cout << "Telefono: ";  cin >> phone;
        cout << "Pais: ";      cin >> country;
        cout << "Categoria: "; cin >> category;
        suppliers->addBack(new Supplier(id, name, email, phone, country, category));
        cout << "Proveedor agregado correctamente!" << endl;
    }
    void filterSupplierByCategory() {
        string category;
        cout << "Ingrese categoria: "; cin >> category;


        auto byCategory = [category](Supplier* s) {
            return s->getProductCategory() == category;
            };
        cout << "\n==== PROVEEDORES EN CATEGORIA: " << category << " ====" << endl;
        suppliers->filter(byCategory);
    }
    void processNextOrder() {
        if (orderQueue->isEmpty()) {
            cout << "No hay pedidos pendientes." << endl;
            return;
        }
        cout << "Procesando pedido:" << endl;
        orderQueue->peek()->show();
        orderQueue->peek()->setStatus("procesando");
        orderQueue->dequeue();
        cout << "Pedido procesado y removido de la cola!" << endl;
    }
    void addProduct() {
        int id, stock;
        string name, category;
        double price;
        cout << "ID: ";       cin >> id;
        cout << "Nombre: ";   cin >> name;
        cout << "Categoria: "; cin >> category;
        cout << "Precio: ";   cin >> price;
        cout << "Stock: ";    cin >> stock;
        products->addBack(new Product(id, name, category, price, stock));
        cout << "Producto agregado correctamente!" << endl;
    }
    void deleteProduct() {
        int id;
        cout << "ID del producto a eliminar: "; cin >> id;
        products->deleteById(id);
    }

    void filterByCategory() {
        string category;
        cout << "Ingrese categoria: "; cin >> category;
        // lambda filtrar por categoria
        auto byCategory = [category](Product* p) {
            return p->getCategory() == category;
            };
        cout << "\n==== PRODUCTOS EN CATEGORIA: " << category << " ====" << endl;
        products->filter(byCategory);
    }
    void filterByPrice() {
        double maxPrice;
        cout << "Ingrese precio maximo: "; cin >> maxPrice;
        // lambda filtrar por precio
        auto byPrice = [maxPrice](Product* p) {
            return p->getPrice() <= maxPrice;
            };
        cout << "\n==== PRODUCTOS HASTA S/." << maxPrice << " ====" << endl;
        products->filter(byPrice);
    }

    ~MenuAdmin() {}



};

