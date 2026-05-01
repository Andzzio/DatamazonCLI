#pragma once
#include "Entity.h"
#include "DoubleList.h"
#include "Product.h"

class MenuAdmin
{
private:
	DoubleList<Product*>* products;
public:
	MenuAdmin(DoubleList<Product*>* products){
		this->products = products;
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
            }
        } while (option != 0);
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

