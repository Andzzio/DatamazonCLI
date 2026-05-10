#pragma once
#include "Entity.h"
#include "DoubleList.h"
#include "Product.h"
#include "Queue.h"    
#include "Order.h"      
#include "Supplier.h"
#include "Invoice.h"
#include "Shipment.h"
#include "InputValidator.h"
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
            option = InputValidator::readNumeric<int>("Elige una opcion: ");
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
        id = InputValidator::readNumeric<int>("ID: ");
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
        Order* orderToProcess = orderQueue->peek();
        orderToProcess->show();
        orderToProcess->setStatus("procesando");
        orderQueue->dequeue();
        
        double totalTax = orderToProcess->getTotal() * 0.18;
        Invoice* invoice = new Invoice(orderToProcess->getId() * 1000, orderToProcess->getId(), "10-05-2026", totalTax, orderToProcess->getTotal() + totalTax);
        invoice->show();

        Shipment* shipment = new Shipment("TRK-" + to_string(orderToProcess->getId()), "Direccion Registrada del Cliente", "Olva Courier");
        shipment->show();

        cout << "Pedido procesado, facturado y enviado!" << endl;
    }
    void addProduct() {
        int id, stock;
        string name, category;
        double price;
        id = InputValidator::readNumeric<int>("ID: ");
        cout << "Nombre: ";   cin >> name;
        cout << "Categoria: "; cin >> category;
        price = InputValidator::readNumeric<double>("Precio: ");
        stock = InputValidator::readNumeric<int>("Stock: ");
        products->addBack(new Product(id, name, category, price, stock));
        cout << "Producto agregado correctamente!" << endl;
    }
    void deleteProduct() {
        int id;
        id = InputValidator::readNumeric<int>("ID del producto a eliminar: ");
        products->deleteById(id);
    }

    void filterByCategory() {
        string category;
        cout << "Ingrese categoria: "; cin >> category;
        auto byCategory = [category](Product* p) {
            return p->getCategory() == category;
            };
        cout << "\n==== PRODUCTOS EN CATEGORIA: " << category << " ====" << endl;
        products->filter(byCategory);
    }
    void filterByPrice() {
        double maxPrice;
        maxPrice = InputValidator::readNumeric<double>("Ingrese precio maximo: ");
        auto byPrice = [maxPrice](Product* p) {
            return p->getPrice() <= maxPrice;
            };
        cout << "\n==== PRODUCTOS HASTA S/." << maxPrice << " ====" << endl;
        products->filter(byPrice);
    }

    ~MenuAdmin() {}
};
