#pragma once
#include <iostream>
#include <string>

using namespace std;

class Payment {
private:
    int paymentId;
    string method;
    double amount;

public:
    Payment(int paymentId, string method, double amount) {
        this->paymentId = paymentId;
        this->method = method;
        this->amount = amount;
    }

    int getPaymentId() { return paymentId; }
    string getMethod() { return method; }
    double getAmount() { return amount; }

    void show() {
        cout << "Pago ID: " << paymentId << " | Metodo: " << method << " | Monto: S/." << amount << endl;
    }

    ~Payment() {}
};
