#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "OrderDetail.h"
#include "DoubleList.h"
#include "Payment.h"
#include "ConsoleUI.h"
using namespace std;

class Order : public Entity {
private:
    int clientId;
    string status;
    double total;
    Payment* payment;
    DoubleList<OrderDetail*>* details;

public:
    Order() {}
    Order(int id, int clientId) : Entity(id) {
        this->clientId = clientId;
        this->status = "pendiente";
        this->total = 0;
        this->payment = nullptr;
        this->details = new DoubleList<OrderDetail*>();
    }

    int    getClientId() { return clientId; }
    string getStatus() { return status; }
    double getTotal() { return total; }
    void   setTotal(double t) { total = t; }
    void   setStatus(string s) { status = s; }
    Payment* getPayment() { return payment; }
    void   setPayment(Payment* p) { payment = p; }

    void addDetail(OrderDetail* detail) {
        details->addBack(detail);
        total += detail->getSubtotal();
    }

    void show() override {
        ConsoleUI::printCardHeader("PEDIDO ID: " + to_string(id));
        ConsoleUI::printCardField("Cliente ID", to_string(clientId));
        ConsoleUI::printCardField("Estado", status);
        ConsoleUI::printCardField("Total", ConsoleUI::formatPrice(total));
        ConsoleUI::printCardFooter();
        
        cout << ConsoleUI::CYAN << "\n[ Detalle del Pedido ]" << ConsoleUI::RESET << endl;
        details->showFrontToBack();

        if (payment != nullptr) {
            cout << ConsoleUI::CYAN << "\n[ Info de Pago ]" << ConsoleUI::RESET << endl;
            payment->show();
        }
    }

    ~Order() {}
};