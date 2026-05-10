#pragma once
#include <iostream>
#include <string>
#include "ConsoleUI.h"

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
        ConsoleUI::printCardField("Pago ID", to_string(paymentId));
        ConsoleUI::printCardField("Metodo", method);
        ConsoleUI::printCardField("Monto", ConsoleUI::formatPrice(amount));
    }

    ~Payment() {}
};
