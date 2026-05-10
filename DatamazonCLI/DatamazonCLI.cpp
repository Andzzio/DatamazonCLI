#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <string>

#include "Admin.h"
#include "Category.h"
#include "Coupon.h"
#include "FileManager.h"
#include "MenuAdmin.h"
#include "MenuClient.h"
#include "Review.h"
#include "SimpleList.h"
#include "Warehouse.h"
#include "InputValidator.h"

using namespace std;

void setColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBanner() {
  setColor(14);
  cout << " ____   _  _____  _     __  __     _     _____  ___  _   _ " << endl;
  cout << "|  _ \\ / \\|_   _|/ \\   |  \\/  |   / \\   |__  / / _ \\| \\ | |"
       << endl;
  cout << "| | | / _ \\ | | / _ \\  | |\\/| |  / _ \\    / / | | | |  \\| |"
       << endl;
  cout << "| |_| / ___ \\| |/ ___ \\ | |  | | / ___ \\  / /_ | |_| | |\\  |"
       << endl;
  cout << "|____/_/   \\_\\_/_/   \\_\\|_|  |_|/_/   \\_\\/____| \\___/|_| \\_|"
       << endl;

  setColor(15);
  cout << "------------------------------------------------------------"
       << endl;
  cout << "      Sistema de Gestion de Inventarios y Marketplace" << endl;
  cout << "       Grupo: 9 | Estructuras de Datos 2026-1" << endl;
  cout << "------------------------------------------------------------"
       << endl;
}

int main() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

  DoubleList<Product *> *products = new DoubleList<Product *>();
  DoubleList<Supplier *> *suppliers = new DoubleList<Supplier *>();
  DoubleList<Client *> *clients = new DoubleList<Client *>();
  SimpleList<Review *> *reviews = new SimpleList<Review *>();
  SimpleList<Category *> *categories = new SimpleList<Category *>();
  DoubleList<Warehouse *> *warehouses = new DoubleList<Warehouse *>();
  Queue<Order *> *orderQueue = new Queue<Order *>();
  SimpleList<Coupon *> *coupons = new SimpleList<Coupon *>();

  FileManager::loadProducts(products);
  FileManager::loadSuppliers(suppliers);
  FileManager::loadClients(clients);

  if (products->count() == 0) {
    products->addBack(new Product(1, "Laptop", "Tecnologia", 2999.99, 10));
    products->addBack(new Product(2, "Auricular", "Tecnologia", 199.99, 25));
    products->addBack(new Product(3, "Polo", "Ropa", 89.99, 50));
    products->addBack(new Product(4, "Libro", "Educacion", 45.00, 30));
    products->addBack(new Product(5, "Celular", "Tecnologia", 1599.99, 8));
    products->addBack(new Product(6, "Mochila", "Ropa", 79.99, 20));
    products->addBack(new Product(7, "Monitor", "Tecnologia", 899.99, 12));
  }

  if (suppliers->count() == 0) {
    suppliers->addBack(new Supplier(1, "TechCorp", "tech@corp.com", "999-111",
                                    "USA", "Tecnologia"));
    suppliers->addBack(new Supplier(2, "FashionPro", "info@fashion.com",
                                    "999-222", "Peru", "Ropa"));
    suppliers->addBack(new Supplier(3, "LibrosMundo", "libros@mundo.com",
                                    "999-333", "Spain", "Educacion"));
  }

  categories->addBack(
      new Category(1, "Tecnologia", "Productos electronicos y gadgets"));
  categories->addBack(
      new Category(2, "Ropa", "Prendas de vestir y accesorios"));
  categories->addBack(
      new Category(3, "Educacion", "Libros y materiales educativos"));

  warehouses->addBack(new Warehouse(1, "Lima-Centro", 1000));
  warehouses->addBack(new Warehouse(2, "Lima-Norte", 500));
  warehouses->addBack(new Warehouse(3, "Arequipa", 300));

  coupons->addBack(new Coupon("DESC10", 10.0));
  coupons->addBack(new Coupon("UPC20", 20.0));

  Admin *adminUser = new Admin(1, "Administrador", "admin@amazonia.com",
                               "999-000", "sixseven", "superadmin");

  auto goodReviews = [](Review *r) { return r->getRating() >= 4; };

  auto byCategory = [](Category *c) { return c->getProductCount() > 0; };

  auto hasSpace = [](Warehouse *w) { return w->getAvailable() > 0; };

  auto isPrime = [](Client *c) { return c->getMembership() == "prime"; };

  auto isPremium = [](Product *p) { return p->getPrice() > 500.0; };

  int option;
  do {
    system("cls");
    printBanner();

    setColor(14);
    cout << "\n  ========================================" << endl;
    setColor(11);
    cout << "  [1] Ingresar como Cliente" << endl;
    cout << "  [2] Ingresar como Administrador" << endl;
    setColor(13);
    cout << "  [3] Ver categorias disponibles" << endl;
    cout << "  [4] Ver almacenes" << endl;
    cout << "  [5] Ver resenas de productos" << endl;
    cout << "  [6] Ver productos premium (S/.>500)" << endl;
    cout << "  [7] Ver clientes prime" << endl;
    setColor(12);
    cout << "  [0] Salir" << endl;
    setColor(14);
    cout << "  ========================================" << endl;
    setColor(15);

    option = InputValidator::readNumeric<int>("\n  Seleccione una opcion: ");

    switch (option) {

    case 1: {
      system("cls");
      setColor(10);
      cout << "==== REGISTRO / LOGIN DE CLIENTE ====" << endl;
      setColor(15);

      string name, email, phone, address, membership;
      int id;
      id = InputValidator::readNumeric<int>("ID: ");
      cout << "Nombre: ";
      cin >> name;
      cout << "Email: ";
      cin >> email;
      cout << "Telefono: ";
      cin >> phone;
      cout << "Direccion: ";
      cin >> address;
      cout << "Membresia (normal/prime): ";
      cin >> membership;

      Client *client = new Client(id, name, email, phone, address, membership);
      clients->addBack(client);

      FileManager::saveClients(clients);

      MenuClient menuClient(client, products, orderQueue, coupons);
      menuClient.show();

      FileManager::saveProducts(products);
      break;
    }

    case 2: {
      system("cls");
      string pass;
      setColor(12);
      cout << "==== ACCESO ADMINISTRADOR ====" << endl;
      setColor(15);
      cout << "Contrasena: ";
      cin >> pass;

      if (adminUser->authenticate(pass)) {
        setColor(10);
        cout << "Bienvenido, " << adminUser->getName() << "!" << endl;
        setColor(15);
        MenuAdmin menuAdmin(products, orderQueue, suppliers);
        menuAdmin.show();

        FileManager::saveProducts(products);
        FileManager::saveSuppliers(suppliers);
      } else {
        setColor(12);
        cout << "Contrasena incorrecta." << endl;
        setColor(15);
        system("pause");
      }
      break;
    }

    case 3: {
      system("cls");
      setColor(13);
      cout << "==== CATEGORIAS DISPONIBLES ====" << endl;
      setColor(15);

      for (auto it = categories->begin(); it != categories->end(); ++it) {
        (*it)->show();
      }

      system("pause");
      break;
    }

    case 4: {
      system("cls");
      setColor(13);
      cout << "==== ALMACENES ====" << endl;
      setColor(15);
      warehouses->showFrontToBack();

      cout << "\n-- Almacenes con espacio disponible --" << endl;
      warehouses->filter(hasSpace);
      system("pause");
      break;
    }

    case 5: {
      system("cls");
      setColor(13);
      cout << "==== RESENAS DE PRODUCTOS ====" << endl;
      setColor(15);

      if (reviews->count() == 0) {
        reviews->addBack(new Review(1, 1, 1, 5, "Excelente laptop!"));
        reviews->addBack(new Review(2, 2, 1, 4, "Buen auricular"));
        reviews->addBack(new Review(3, 3, 2, 3, "Talla normal"));
        reviews->addBack(new Review(4, 5, 1, 5, "Celular rapido"));
      }

      cout << "-- Todas las resenas --" << endl;
      for (auto it = reviews->begin(); it != reviews->end(); ++it) {
        (*it)->show();
      }

      cout << "\n-- Solo resenas buenas (4-5 estrellas) --" << endl;
      reviews->filter(goodReviews);
      system("pause");
      break;
    }

    case 6: {
      system("cls");
      setColor(14);
      cout << "==== PRODUCTOS PREMIUM (S/.>500) ====" << endl;
      setColor(15);
      products->filter(isPremium);
      system("pause");
      break;
    }

    case 7: {
      system("cls");
      setColor(11);
      cout << "==== CLIENTES CON MEMBRESIA PRIME ====" << endl;
      setColor(15);
      if (clients->count() == 0) {
        cout << "No hay clientes registrados aun." << endl;
      } else {
        clients->filter(isPrime);
      }
      system("pause");
      break;
    }

    case 0:
      FileManager::saveProducts(products);
      FileManager::saveSuppliers(suppliers);
      FileManager::saveClients(clients);
      setColor(14);
      cout << "\n  Gracias por usar Amazonia UPC Store!" << endl;
      cout << "  Datos guardados correctamente." << endl;
      setColor(15);
      break;
    }

  } while (option != 0);

  return 0;
}