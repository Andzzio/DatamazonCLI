#include <iostream>
#include"Entity.h"
#include "MenuClient.h"
#include "MenuAdmin.h"
using namespace std;

int main()
{

    DoubleList<Product*>* products = new DoubleList<Product*>();

    products->addBack(new Product(1, "Laptop", "Tecnologia", 2999.99, 10));
    products->addBack(new Product(2, "Auricular", "Tecnologia", 199.99, 25));
    products->addBack(new Product(3, "Polo", "Ropa", 89.99, 50));
    products->addBack(new Product(4, "Libro", "Educacion", 45.00, 30));
    products->addBack(new Product(5, "Celular", "Tecnologia", 1599.99, 8));
    int option;
    do {
        cout << "1. Ingresar como Cliente" << endl;
        cout << "2. Ingresar como Administrador" << endl;
        cout << "0. Salir" << endl;
        cout << "Elige una opcion: "; cin >> option;
        system("cls");

        switch (option) {
        case 1: {
            // Login simple del cliente
            string name, email, phone, address, membership;
            int id;
            cout << "==== REGISTRO DE CLIENTE ====" << endl;
            cout << "ID: ";          cin >> id;
            cout << "Nombre: ";      cin >> name;
            cout << "Email: ";       cin >> email;
            cout << "Telefono: ";    cin >> phone;
            cout << "Direccion: ";   cin >> address;
            cout << "Membresia (normal/prime): "; cin >> membership;

            Client* client = new Client(id, name, email, phone, address, membership);
            MenuClient menuClient(client, products);
            menuClient.show();
            break;
        }
        case 2: {
         
            string pass;
            cout << "Contrasena admin: "; cin >> pass;
            if (pass == "andrekabrazo") {
                MenuAdmin menuAdmin(products);
                menuAdmin.show();
            }
            else {
                cout << "Contrasena incorrecta." << endl;
            }
            break;
        }
        }
    } while (option != 0);

    cout << "Gracias por usar amazonas!" << endl;
    return 0;
}

