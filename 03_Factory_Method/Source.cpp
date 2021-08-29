#include <iostream>
using namespace std;

class User
{
public:
	virtual void Info() = 0;

};

class Admin : public User
{
public:
	virtual void Info()
	{
		cout << "I`m admin";
	}
};

class Manager : public User
{
public:
	virtual void Info()
	{
		cout << "I`m manager";
	}
};

class Guest : public User
{
public:
	virtual void Info()
	{
		cout << "I`m guest";
	}
};

enum UserTypes { ADMIN, GUEST, MANAGER };

UserTypes ReadUserTypeFromFile()
{
	return UserTypes::ADMIN;
}

class UserFactory
{
public:
	User* CreateUser(UserTypes type)
	{
		switch (type)
		{
		case ADMIN:
			return new Admin();
		case MANAGER:
			return new Manager();
		case GUEST:
			return new Guest();
		}
	}
};

void main()
{
	UserFactory factory;

	UserTypes type = ReadUserTypeFromFile();
	User* user = factory.CreateUser(type);

	user->Info();

	cout << endl;
	system("pause");
}