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

void printBanner() {
  cout << ConsoleUI::MAGENTA << ConsoleUI::BOLD << endl;
  cout << " ____   _  _____  _     __  __     _     _____  ___  _   _ " << endl;
  cout << "|  _ \\ / \\|_   _|/ \\   |  \\/  |   / \\   |__  / / _ \\| \\ | |" << endl;
  cout << "| | | / _ \\ | | / _ \\  | |\\/| |  / _ \\    / / | | | |  \\| |" << endl;
  cout << "| |_| / ___ \\| |/ ___ \\ | |  | | / ___ \\  / /_ | |_| | |\\  |" << endl;
  cout << "|____/_/   \\_\\_/_/   \\_\\|_|  |_|/_/   \\_\\/____| \\___/|_| \\_|" << endl;
  cout << ConsoleUI::RESET << endl;

  ConsoleUI::printHeader("Sistema de Gestion de Inventarios y Marketplace");
  cout << ConsoleUI::CYAN << "           Grupo: 9 | Estructuras de Datos 2026-1" << ConsoleUI::RESET << endl;
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

    ConsoleUI::printMenuOption(1, "Ingresar como Cliente");
    ConsoleUI::printMenuOption(2, "Ingresar como Administrador");
    ConsoleUI::printMenuOption(3, "Ver categorias disponibles");
    ConsoleUI::printMenuOption(4, "Ver almacenes");
    ConsoleUI::printMenuOption(5, "Ver resenas de productos");
    ConsoleUI::printMenuOption(6, "Ver productos premium (S/.>500)");
    ConsoleUI::printMenuOption(7, "Ver clientes prime");
    ConsoleUI::printMenuOption(0, "Salir");

    option = InputValidator::readNumeric<int>("\n  Seleccione una opcion: ");

    switch (option) {

    case 1: {
      system("cls");
      ConsoleUI::printHeader("REGISTRO / LOGIN DE CLIENTE");

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
      ConsoleUI::printHeader("ACCESO ADMINISTRADOR");
      cout << "Contrasena: ";
      cin >> pass;

      if (adminUser->authenticate(pass)) {
        ConsoleUI::printSuccess("Bienvenido, " + adminUser->getName() + "!");
        MenuAdmin menuAdmin(products, orderQueue, suppliers);
        menuAdmin.show();

        FileManager::saveProducts(products);
        FileManager::saveSuppliers(suppliers);
      } else {
        ConsoleUI::printError("Contrasena incorrecta.");
        system("pause");
      }
      break;
    }

    case 3: {
      system("cls");
      ConsoleUI::printHeader("CATEGORIAS DISPONIBLES");

      for (auto it = categories->begin(); it != categories->end(); ++it) {
        (*it)->show();
      }

      system("pause");
      break;
    }

    case 4: {
      system("cls");
      ConsoleUI::printHeader("ALMACENES");
      warehouses->showFrontToBack();

      cout << "\n-- Almacenes con espacio disponible --" << endl;
      warehouses->filter(hasSpace);
      system("pause");
      break;
    }

    case 5: {
      system("cls");
      ConsoleUI::printHeader("RESENAS DE PRODUCTOS");

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
      ConsoleUI::printHeader("PRODUCTOS PREMIUM (S/.>500)");
      ConsoleUI::printProductTableHeader();
      products->filter(isPremium);
      ConsoleUI::printProductTableFooter();
      system("pause");
      break;
    }

    case 7: {
      system("cls");
      ConsoleUI::printHeader("CLIENTES CON MEMBRESIA PRIME");
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
      ConsoleUI::printSuccess("Gracias por usar Amazonia UPC Store!");
      ConsoleUI::printSuccess("Datos guardados correctamente.");
      break;
    }

  } while (option != 0);

  return 0;
}