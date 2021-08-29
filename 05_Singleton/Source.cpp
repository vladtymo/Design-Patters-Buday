#include <iostream>
#include <string>
using namespace std;

// Singleton with destructor
class Singleton
{
private:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(Singleton&) = delete;
public:
	static Singleton& GetInstance() {
		static Singleton instance;
		return instance;
	}

	void Log(string msg)
	{
		cout << "Msg: " << msg << endl;
	}
};

int main()
{
	Singleton& single = Singleton::GetInstance();
	single.Log("Hello from logger!");
	Singleton::GetInstance().Log("Insert new user at 19:57PM");
	Singleton::GetInstance().Log("Delete user Bob at 10:44PM");
	Singleton::GetInstance().Log("Clear all user data at 04:20PM");

	system("pause");
	return 0;
}