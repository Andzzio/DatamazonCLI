#pragma once
#include <iostream>
#include <string>
#include "ConsoleUI.h"

using namespace std;

class Invoice {
private:
    int invoiceId;
    int orderId;
    string date;
    double totalTax;
    double totalAmount;

public:
    Invoice(int invoiceId, int orderId, string date, double totalTax, double totalAmount) {
        this->invoiceId = invoiceId;
        this->orderId = orderId;
        this->date = date;
        this->totalTax = totalTax;
        this->totalAmount = totalAmount;
    }

    int getInvoiceId() { return invoiceId; }
    int getOrderId() { return orderId; }
    string getDate() { return date; }
    double getTotalTax() { return totalTax; }
    double getTotalAmount() { return totalAmount; }

    void show() {
        ConsoleUI::printCardHeader("BOLETA DE VENTA");
        ConsoleUI::printCardField("Boleta Nro", to_string(invoiceId));
        ConsoleUI::printCardField("Pedido", to_string(orderId));
        ConsoleUI::printCardField("Fecha", date);
        ConsoleUI::printCardField("Impuestos (18%)", ConsoleUI::formatPrice(totalTax));
        ConsoleUI::printCardField("Total General", ConsoleUI::formatPrice(totalAmount));
        ConsoleUI::printCardFooter();
    }

    ~Invoice() {}
};
