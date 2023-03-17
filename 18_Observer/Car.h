#pragma once
#include"Product.h"

// ConcreteSubject - клас конкретного продукта (автомобіль)
class Car : public Product
{
public:
	Car(string name, double price) :Product(name, price) {}
};