#include <iostream>
#include <string>
using namespace std;

// Prototype Interface
template<class T>
class Prototype
{
public:
	virtual T Clone() const = 0;
};

struct Date
{
	int year, month, day;

	string ToString() const
	{
		return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}
};

class Member : public Prototype<Member>
{
private:
	string name;
	int age;
public:
	Member() : name("no name"), age(0) { }
	Member(string name, int age) : name(name), age(age) { }

	Member Clone() const
	{
		return *this;
	}

	string ToString() const
	{
		return name + to_string(age);
	}
};

class Event : public Prototype<Event>
{
private:
	string name;
	Date date;
	string address;
	Member* members;
	int membersCount;
public:
	Event() : name("no name"), date(Date{ 0, 0, 0 }), address("no address") { }
	Event(string name, Date date, string address) : name(name), date(date), address(address) { }

	void AddTestMembers()
	{
		membersCount = 2;
		members = new Member[membersCount];

		members[0] = Member("Bob", 30);
		members[1] = Member("Vova", 44);
	}

	Event Clone() const override
	{
		Event clone = *this;
		clone.members = new Member[membersCount];
		for (int i = 0; i < membersCount; i++)
		{
			clone.members[i] = this->members[i].Clone();
		}
		return clone;
	}

	string ToString() const
	{
		string res = name + " : " + date.ToString() + "\n" + address;
		for (int i = 0; i < membersCount; i++)
		{
			res += "\n\tMember[" + to_string(i + 1) + "] - " + members[i].ToString();
		}
		return res;
	}
};

void main()
{
	// testing...
	Event event1("Independence Day", Date{ 2021, 8, 24 }, "Kyiv, Ukraine");
	// initializing...
	event1.AddTestMembers();

	cout << event1.ToString() << endl;

	Event cloneEvent = event1.Clone();

	cout << cloneEvent.ToString() << endl;
}