#pragma once
#include <string>
#include<list>
#include<iostream>

using namespace std;

class Buyer;

// Subject - в нашому випадку це клас Product, який описує абстрактний продукт

class Product
{
private:
	// назва 
	string name;
	// ціна
	double price;
	// потенційні покупці, які зацікавлені
	list<Buyer*> buyers;

public:

	Product(string, double);
	~Product();

public:
	// додавання конкретного покупця
	void Attach(Buyer*);
	// видалення конкретного покупця
	void Detach(Buyer*);
	// повідомлення всіх покупців про зміну стану
	void Notify();

public:

	string GetName() const
	{
		return name;
	}

	double GetPrice() const
	{
		return price;
	}
	// встановлення нової ціни та інформування покупців про це
	void SetPrice(double pPrice)
	{
		if (price != pPrice)
		{
			price = pPrice;
			Notify();
		}
	}
};