#pragma once
#include "Entity.h"
#include "ConsoleUI.h"

class Product :public Entity
{
protected:
	string name;
	string category;
	double price;
	int stock;

public:

	Product(int id, string name, string category, double price, int stock) : Entity(id) {
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
		ConsoleUI::printTableRow5(to_string(id), 5, name, 20, category, 15, ConsoleUI::formatPrice(price), 15, to_string(stock), 8);
	}

	~Product() {};
};

