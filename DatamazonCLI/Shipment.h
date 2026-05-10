#pragma once
#include <iostream>
#include <string>
#include "ConsoleUI.h"

using namespace std;

class Shipment {
private:
    string trackingCode;
    string destination;
    string courier;

public:
    Shipment(string trackingCode, string destination, string courier) {
        this->trackingCode = trackingCode;
        this->destination = destination;
        this->courier = courier;
    }

    string getTrackingCode() { return trackingCode; }
    string getDestination() { return destination; }
    string getCourier() { return courier; }

    void show() {
        ConsoleUI::printCardHeader("GUIA DE ENVIO");
        ConsoleUI::printCardField("Tracking", trackingCode);
        ConsoleUI::printCardField("Destino", destination);
        ConsoleUI::printCardField("Courier", courier);
        ConsoleUI::printCardFooter();
    }

    ~Shipment() {}
};
