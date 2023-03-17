#include "Product.h"
#include "Buyer.h"


Product::Product(string pName, double pPrice) : name(pName), price(pPrice) { }

Product::~Product() { }

void Product::Attach(Buyer* pBuyer)
{
	buyers.push_back(pBuyer);
}
void Product::Detach(Buyer* pBuyer)
{
	for (auto it = buyers.begin(); it != buyers.end();it++)
	{
		if(*it == pBuyer)
		{
			buyers.erase(it);
			return;
		}
	}
}
void Product::Notify()
{
	for (auto it = buyers.begin(); it != buyers.end();it++)
	{
		(*it)->Update(this);
	}
	cout << "\n";
}
