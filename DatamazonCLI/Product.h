#pragma once
#include "Entity.h"

class Product :public Entity
{
protected:
	string name;
	string category;
	double price;
	int stock;

public:

	Product(int id, string name, string category, double price, int stock): Entity(id) {
		this->name = name;
		this->category = category;
		this->price = price;
		this->stock = stock;
	}
	string getName() { return name; }
	string getCategory() { return category; }
	double getPrice() { return price; }

	//aña aña
	int    getStock() { return stock; }
	void   setStock(int s) { stock = s; }

	void show() override {
		cout << "Producto: " << name << " | Precio: S/." << price
			<< " | Stock: " << stock << endl;
	}

	~Product() {};
};

