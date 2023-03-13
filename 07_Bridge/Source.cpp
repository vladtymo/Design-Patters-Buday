#include <iostream>
using namespace std;

// abstract
class WallCreator
{
public:
	virtual void BuildWall() = 0;
	virtual void BuildWallWithDoor() = 0;
	virtual void BuildWallWithWindow() = 0;
};

// abstract
class Company
{
protected:
	WallCreator* _wallCreator; // implementation
public:
	void SetWallCreator(WallCreator* wallCreator)
	{
		_wallCreator = wallCreator;
	}
	virtual void BuildFoundation() = 0;
	virtual void BuildRoom() = 0;
	virtual void BuildRoof() = 0;
};

class BuldingCompany : public Company
{
public:
	void BuildFoundation()
	{
		cout << "Foundation is built.\n";
	}
	void BuildRoom()
	{
		_wallCreator->BuildWallWithDoor();
		_wallCreator->BuildWall();
		_wallCreator->BuildWallWithWindow();
		_wallCreator->BuildWall();

		cout << "Room finished.\n";
	}
	void BuildRoof()
	{
		cout << "Roof is done.\n";
	}
};

class BrickWallCreator : public WallCreator
{
public:
	void BuildGrage()
	{
		cout << "Brick garage created!";
	}

	void BuildWall()
	{
		cout << "Brick wall created!";
	}

	void BuildWallWithDoor()
	{
		cout << "Brick wall with door created!";
	}

	void BuildWallWithWindow()
	{
		cout << "Brick wall with window created!";
	}
};

class ConcreteSlabWallCreator : public WallCreator
{
public:
	void BuildGrage()
	{
		cout << "Concrete garage created!";
	}

	void BuildWall()
	{
		cout << "Concrete wall created!";
	}

	void BuildWallWithDoor()
	{
		cout << "Concrete wall with door created!";
	}

	void BuildWallWithWindow()
	{
		cout << "Concrete wall with window created!";
	}
};

class WoodenWallCreator : public WallCreator
{
public:
	void BuildGrage()
	{
		cout << "Wooden garage created!";
	}

	void BuildWall()
	{
		cout << "Wooden wall created!";
	}

	void BuildWallWithDoor()
	{
		cout << "Wooden wall with door created!";
	}

	void BuildWallWithWindow()
	{
		cout << "Wooden wall with window created!";
	}
};

void main()
{
	BuldingCompany buildingCompany = BuldingCompany();

	buildingCompany.BuildFoundation();

	buildingCompany.SetWallCreator(new BrickWallCreator());
	buildingCompany.BuildRoom();
	buildingCompany.SetWallCreator(new ConcreteSlabWallCreator());
	buildingCompany.BuildRoom();
	buildingCompany.SetWallCreator(new WoodenWallCreator());
	buildingCompany.BuildRoom();

	buildingCompany.BuildRoof();

	system("pause");
}