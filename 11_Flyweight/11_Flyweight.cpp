#include <iostream>
#include <map>
using namespace std;

// flyweight object factory
enum PType { GOBLIN, DRAGON };
class UnitPictureFactory
{
private:
    static map<PType, uint8_t*> pictures;

public:
    static uint8_t* GetGoblinPicture()
    {
        if (pictures.count(PType::GOBLIN) == 0)
            pictures[PType::GOBLIN] = new uint8_t[1024 * 1024 * 10]; // 10 MB

        return pictures[PType::GOBLIN];
    }
    static uint8_t* GetDragonPicture()
    {
        if (pictures.count(PType::DRAGON) == 0)
            pictures[PType::DRAGON] = new uint8_t[1024 * 1024 * 5]; // 5 MB

        return pictures[PType::DRAGON];
    }

    static void ClearCache()
    {
        for (auto item : pictures)
        {
            delete[] item.second;
        }
        pictures.clear();
    }
};

// abstract class
class Unit
{
protected:
    string name;
    int health;
    uint8_t* picture;

public:
    Unit() : name(""), health(0), picture(nullptr) { }
    virtual ~Unit() { };
};

class Goblin : public Unit
{
public:
    Goblin()
    {
        name = "Goblin";
        health = 100;
        //picture = new uint8_t[1024 * 1024]; // 1 MB
        picture = UnitPictureFactory::GetGoblinPicture();
    }
};

class Dragon : public Unit
{
public:
    Dragon()
    {
        name = "Dragon";
        health = 100;
        picture = UnitPictureFactory::GetDragonPicture();
    }
};

class Game
{
private:
    Unit** units;
    int count;

public:
    Game()
    {
        count = 100;
        units = new Unit * [count];

        for (size_t i = 0; i < count/2; i++)
        {
            units[i] = new Goblin();
        }
        for (size_t i = count/2; i < count; i++)
        {
            units[i] = new Dragon();
        }
    }
    ~Game()
    {
        for (size_t i = 0; i < count; i++)
        {
            delete units[i];
        }
    }
};

map<PType, uint8_t*> UnitPictureFactory::pictures = map<PType, uint8_t*>();

int main()
{
    Game game; // allocate memory (>75 MB)

    UnitPictureFactory::ClearCache();
    cin.get();
}
