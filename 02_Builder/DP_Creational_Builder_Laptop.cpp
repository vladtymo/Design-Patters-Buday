#include <iostream>
#include <string>
using namespace std;

//////////////////
// Creational Pattern: Builder
class Laptop
{
private:
    string screenResolution;
    string proccessor;
    string memory;
    string hdd;
    string battery;
public:

	void SetResolution(string value) { screenResolution = value; }
	void SetProccessor(string value) { proccessor = value; }
	void SetMemory(string value) { memory = value; }
	void SetHDD(string value) { hdd = value; }
	void SetBattery(string value) { battery = value; }

    void Show() const
    {
        cout << "Screen Resolution: " << screenResolution << endl;
        cout << "Proccessor: " << proccessor << endl;
        cout << "Memory: " << memory << endl;
        cout << "HDD: " << hdd << endl;
        cout << "Battery: " << battery << endl;
    }
};

class LaptopBuilder
{
protected:
    Laptop * laptop;
public:
    void CreateNewLaptop()
    {
        laptop = new Laptop();
    }
    // Метод, який повертає готовий ноутбук назовні
    Laptop * GetMyLaptop() const
    {
        return laptop;
    }
    // Кроки, необхідні щоб створити ноутбук
    virtual void SetMonitorResolution() = 0;
    virtual void SetProcessor() = 0;
    virtual void SetMemory() = 0;
    virtual void SetHDD() = 0;
    virtual void SetBattery() = 0;
};

// Таким будівельником може бути працівник, що
// спеціалізується у складанні «геймерських» ноутів
class GamingLaptopBuilder : public LaptopBuilder
{
    void SetMonitorResolution() override
    {
        laptop->SetResolution("1900X1200");
    }
    void SetProcessor() override
    {
        laptop->SetProccessor("Intel Core i7, 2.9GHz");
    }
    void SetMemory() override
    {
        laptop->SetMemory("16 Gb");
    }
    void SetHDD() override
    {
        laptop->SetHDD("1 TB");
    }
    void SetBattery() override
    {
        laptop->SetBattery("12 lbs");
    }
};

// А ось інший «збирач» ноутів
class TripLaptopBuilder : public LaptopBuilder
{
    void SetMonitorResolution()
    {
        laptop->SetResolution("1200X900");
    }
	void SetProcessor() override
	{
		laptop->SetProccessor("Core 2 Duo, 3.2 GHz");
	}
	void SetMemory() override
	{
		laptop->SetMemory("6144 Mb");
	}
	void SetHDD() override
	{
		laptop->SetHDD("500 Gb");
	}
	void SetBattery() override
	{
		laptop->SetBattery("6 lbs");
	}
};

class LaptopDirector
{
    LaptopBuilder * builder;
public:
	LaptopDirector(LaptopBuilder* builder = nullptr) : builder(builder) { }
	~LaptopDirector()
	{
		if (builder != nullptr) delete builder;
	}

    void SetBuilder(LaptopBuilder * b)
    {
        builder = b;
    }
    Laptop * GetLaptop() const
    {
		// Повернення готового ноутбука
        return builder->GetMyLaptop();
    }
    void Configurate()
    {
        // Створення ноутбука
        builder->CreateNewLaptop();
        // Етапи його побудови
        builder->SetMonitorResolution();
        builder->SetProcessor();
        builder->SetMemory();
        builder->SetHDD();
        builder->SetBattery();
    }
};

void main()
{
    LaptopDirector dir;
    dir.SetBuilder(new GamingLaptopBuilder()); // new TripLaptopBuilder()
    dir.Configurate();
    Laptop * laptop = dir.GetLaptop();

    laptop->Show();

	// clear resources
	delete laptop;
}