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
            system("cls");
            ConsoleUI::printHeader("AMAZONIA - ADMINISTRADOR");
            ConsoleUI::printMenuOption(1, "Ver todos los productos");
            ConsoleUI::printMenuOption(2, "Agregar producto");
            ConsoleUI::printMenuOption(3, "Eliminar producto");
            ConsoleUI::printMenuOption(4, "Filtrar por categoria");
            ConsoleUI::printMenuOption(5, "Filtrar por precio maximo");
            ConsoleUI::printMenuOption(6, "Ver cola de pedidos");
            ConsoleUI::printMenuOption(7, "Procesar siguiente pedido");
            ConsoleUI::printMenuOption(8, "Ver proveedores");
            ConsoleUI::printMenuOption(9, "Agregar proveedor");
            ConsoleUI::printMenuOption(10, "Buscar proveedor por categoria");
            ConsoleUI::printMenuOption(0, "Cerrar sesion");
            option = InputValidator::readNumeric<int>("Elige una opcion: ");
            system("cls");

            switch (option) {
            case 1:
                ConsoleUI::printProductTableHeader();
                products->showFrontToBack();
                ConsoleUI::printProductTableFooter();
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
                ConsoleUI::printHeader("TODOS LOS PROVEEDORES");
                ConsoleUI::printSupplierTableHeader();
                suppliers->showFrontToBack();
                ConsoleUI::printSupplierTableFooter();
                break;
            case 9:
                addSupplier();
                break;
            case 10:
                filterSupplierByCategory();
                break;
            }
            
            if (option != 0) {
                cout << "\n";
                system("pause");
            }
        } while (option != 0);
    }
    void addSupplier() {
        int id;
        string name, email, phone, country, category;
        ConsoleUI::printHeader("NUEVO PROVEEDOR");
        id = InputValidator::readNumeric<int>("ID: ");
        cout << "Nombre: ";    cin >> name;
        cout << "Email: ";     cin >> email;
        cout << "Telefono: ";  cin >> phone;
        cout << "Pais: ";      cin >> country;
        cout << "Categoria: "; cin >> category;
        suppliers->addBack(new Supplier(id, name, email, phone, country, category));
        ConsoleUI::printSuccess("Proveedor agregado correctamente!");
    }
    void filterSupplierByCategory() {
        string category;
        cout << "Ingrese categoria: "; cin >> category;

        auto byCategory = [category](Supplier* s) {
            return s->getProductCategory() == category;
            };
        ConsoleUI::printHeader("PROVEEDORES EN CATEGORIA: " + category);
        ConsoleUI::printSupplierTableHeader();
        suppliers->filter(byCategory);
        ConsoleUI::printSupplierTableFooter();
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
        ConsoleUI::printSuccess("Producto agregado correctamente!");
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
        ConsoleUI::printHeader("PRODUCTOS EN CATEGORIA: " + category);
        ConsoleUI::printProductTableHeader();
        products->filter(byCategory);
        ConsoleUI::printProductTableFooter();
    }
    void filterByPrice() {
        double maxPrice;
        maxPrice = InputValidator::readNumeric<double>("Ingrese precio maximo: ");
        auto byPrice = [maxPrice](Product* p) {
            return p->getPrice() <= maxPrice;
            };
        ConsoleUI::printHeader("PRODUCTOS HASTA S/." + ConsoleUI::formatPrice(maxPrice));
        ConsoleUI::printProductTableHeader();
        products->filter(byPrice);
        ConsoleUI::printProductTableFooter();
    }

    ~MenuAdmin() {}
};
