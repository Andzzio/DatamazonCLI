#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "OrderDetail.h"
#include "DoubleList.h"
#include "Payment.h"
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
        cout << "#################################" << endl;
        cout << "  Pedido ID : " << id << endl;
        cout << "  Cliente ID: " << clientId << endl;
        cout << "  Estado    : " << status << endl;
        cout << "  Detalle   :" << endl;
        details->showFrontToBack();
        cout << "  Total     : S/." << total << endl;
        if (payment != nullptr) {
            payment->show();
        }
        cout << "##################################" << endl;
    }

    ~Order() {}
};