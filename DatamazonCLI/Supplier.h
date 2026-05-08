#pragma once
#include "Entity.h"
#include <string>
using namespace std;

class Supplier : public Entity {
private:
    string name;
    string email;
    string phone;
    string country;
    string productCategory;

public:
    Supplier() {}
    Supplier(int id, string name, string email, string phone,
        string country, string productCategory) : Entity(id) {
        this->name = name;
        this->email = email;
        this->phone = phone;
        this->country = country;
        this->productCategory = productCategory;
    }

    string getName() { return name; }
    string getEmail() { return email; }
    string getPhone() { return phone; }
    string getCountry() { return country; }
    string getProductCategory() { return productCategory; }

    void show() override {
        cout << "--------------------------" << endl;
        cout << "  Proveedor : " << name << endl;
        cout << "  Email     : " << email << endl;
        cout << "  Telefono  : " << phone << endl;
        cout << "  Pais      : " << country << endl;
        cout << "  Categoria : " << productCategory << endl;
        cout << "-------------------------" << endl;
    }

    ~Supplier() {}
};