#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "OrderDetail.h"
#include "DoubleList.h"
using namespace std;

class Order : public Entity {
private:
    int clientId;
    string status;   // "pendiente", "procesando", "enviado", "entregado"
    double total;
    DoubleList<OrderDetail*>* details;

public:
    Order() {}
    Order(int id, int clientId) : Entity(id) {
        this->clientId = clientId;
        this->status = "pendiente";
        this->total = 0;
        this->details = new DoubleList<OrderDetail*>();
    }

    int    getClientId() { return clientId; }
    string getStatus() { return status; }
    double getTotal() { return total; }
    void   setStatus(string s) { status = s; }

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
        cout << "##################################" << endl;
    }

    ~Order() {}
};