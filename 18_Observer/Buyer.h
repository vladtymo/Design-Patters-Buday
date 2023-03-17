#pragma once
#include <string>
#include "Product.h"

using namespace std;

// Observer - клас потенційного покупця
class Buyer
{
public:
	// інформування про зміну стану
	virtual void Update(Product*) = 0;
};

// ConcreteObserver - клас для українських покупців
class UkrainianBuyer : public Buyer
{
private:
	Product* ptr;
	string name;
public:
	UkrainianBuyer(string pName)
	{
		name = pName;
	}
	Product* GetProduct() const
	{
		return ptr;
	}
	void SetProduct(Product* pProduct)
	{
		ptr = pProduct;
	}
	void Update(Product* pProduct)
	{
		// business logic
		cout << "\nChanges for " << name << " in product " << pProduct->GetName() << " " << pProduct->GetPrice();
	}
};