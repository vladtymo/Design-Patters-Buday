#include <iostream>
#include <string>
using namespace std;

// class hierarchy for file compression operation types
class Compression
{
public:
	virtual ~Compression() {}
	virtual void compress(const string& file) = 0;
};

class ZIP_Compression : public Compression
{
public:
	void compress(const string& file) override {
		cout << "ZIP compression: " << file << " -> .zip" << endl;
	}
};

class ARJ_Compression : public Compression
{
public:
	void compress(const string& file) override {
		cout << "ARJ compression" << file << " -> .arj" << endl;
	}
};

class RAR_Compression : public Compression
{
public:
	void compress(const string& file) override {
		cout << "RAR compression" << file << " -> .rar" << endl;
	}
};

// client usage class
class Compressor
{
public:
	Compressor(Compression* comp) : p(comp) {}
	~Compressor() { delete p; }

	void compress(const string& file) {
		// open file
		p->compress(file);
		// save file
	}

	void SetStrategy(Compression* new_p)
	{
		delete p;
		p = new_p;
	}
private:
	Compression* p;
};


int main()
{
	Compressor p = Compressor(new ZIP_Compression);
	p.compress("file.txt");

	p.SetStrategy(new RAR_Compression);
	p.compress("file.txt");

	p.SetStrategy(new ARJ_Compression);
	p.compress("Program.cs");
	p.compress("database.dmb");

	system("pause");
	return 0;
}
