#pragma once
#include "Client.h"
#include "Coupon.h"
#include "DoubleList.h"
#include "Order.h"
#include "Payment.h"
#include "Product.h"
#include "Queue.h"
#include "SimpleList.h"
#include "Stack.h"
#include "InputValidator.h"
#include <iostream>
using namespace std;
class MenuClient {
private:
  Client *client;
  DoubleList<Product *> *products;
  Stack<Product *> *cartHistory;
  Queue<Order *> *orderQueue;
  SimpleList<Coupon *> *coupons;

  int orderCounter;

public:
  MenuClient(Client *client, DoubleList<Product *> *products,
             Queue<Order *> *orderQueue, SimpleList<Coupon *> *coupons) {
    this->client = client;
    this->products = products;
    this->orderQueue = orderQueue;
    this->coupons = coupons;
    cartHistory = new Stack<Product *>();
    orderCounter = 1;
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
      cout << "5. Realizar pedido" << endl;
      cout << "6. Ver mis pedidos en cola" << endl;
      cout << "0. Cerrar sesion" << endl;
      option = InputValidator::readNumeric<int>("Elige una opcion: ");
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
      case 5:
        createOrder();
        break;
      case 6:
        orderQueue->showAll();
      }

    } while (option != 0);
  }

private:
  void showProducts() {
    cout << "\n==== PRODUCTOS DISPONIBLES ====" << endl;
    auto hasStock = [](Product *p) { return p->getStock() > 0; };
    products->filter(hasStock);
  }

  void searchProduct() {
    string name;
    cout << "Ingrese nombre del producto: ";
    cin >> name;
    auto byName = [name](Product *p) { return p->getName() == name; };
    cout << "\n==== RESULTADO ====" << endl;
    products->filter(byName);
  }

  void addToCart() {
    int id;
    id = InputValidator::readNumeric<int>("Ingrese ID del producto: ");
    Node<Product *> *current = products->head;
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
  void createOrder() {
    int id, quantity;
    Order *order = new Order(orderCounter++, client->getId());

    cout << "\n==== NUEVO PEDIDO ====" << endl;
    char addMore = 's';
    while (addMore == 's') {
      id = InputValidator::readNumeric<int>("ID del producto: ");
      quantity = InputValidator::readNumeric<int>("Cantidad: ");

      Node<Product *> *current = products->head;
      while (current != nullptr) {
        if (current->value->getId() == id) {
          if (current->value->getStock() >= quantity) {
            order->addDetail(new OrderDetail(id, current->value, quantity));
            current->value->setStock(current->value->getStock() - quantity);
            cout << "Producto agregado al pedido!" << endl;
          } else {
            cout << "Stock insuficiente." << endl;
          }
          break;
        }
        current = current->next;
      }

      cout << "Agregar otro producto? (s/n): ";
      cin >> addMore;
    }

    char hasCoupon;
    cout << "¿Tiene un codigo de cupon? (s/n): ";
    cin >> hasCoupon;
    if (hasCoupon == 's' || hasCoupon == 'S') {
      string code;
      cout << "Ingrese codigo de cupon: ";
      cin >> code;
      bool found = false;
      for (auto it = coupons->begin(); it != coupons->end(); ++it) {
        if ((*it)->getCode() == code) {
          double desc = (*it)->getDiscountPercent();
          cout << "Cupon aplicado! Descuento del " << desc << "%" << endl;
          double nuevoTotal = order->getTotal() * (1.0 - (desc / 100.0));
          order->setTotal(nuevoTotal);
          found = true;
          break;
        }
      }
      if (!found) {
        cout << "Cupon invalido." << endl;
      }
    }

    int payMethodOption;
    string methodStr = "Efectivo";
    cout << "\nTotal a pagar: S/." << order->getTotal() << endl;
    payMethodOption = InputValidator::readNumeric<int>("Metodo de pago (1. Tarjeta, 2. Efectivo): ");
    if (payMethodOption == 1)
      methodStr = "Tarjeta";

    Payment *payment =
        new Payment(orderCounter * 100, methodStr, order->getTotal());
    order->setPayment(payment);

    orderQueue->enqueue(order);
    cout << "Pedido realizado y pagado con " << methodStr
         << "! Posicion en cola: " << orderQueue->count() << endl;
  }
};