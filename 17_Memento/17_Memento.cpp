#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

struct GameState
{
	double health;
	int killedMonsters;
	string saveTime;

	GameState() { }
	GameState(double health, int killedMonsters)
	{
		this->health = health;
		this->killedMonsters = killedMonsters;
		this->saveTime = "17.03.2023";
	}

	void Show()
	{
		cout << "Health: " << health << "\nKilled Monsters: " << killedMonsters << "\nST " << saveTime << endl;
		cout << "-----------------------\n";
	}
};

class GameMemento
{
private:
	GameState _state;

public:
	GameMemento(GameState state)
	{
		_state = state;
	}

	GameState GetState()
	{
		return _state;
	}

	void Show()
	{
		cout << "From Memento - ";
		_state.Show();
	}
};

class GameOriginator
{
private:
	GameState _state; //Health & Killed Monsters

public:
	GameOriginator()
	{
		_state = GameState(100, 0);
	}
	void Play()
	{
		//During this Play method game's state is continuously changed	
		_state = GameState((int)(_state.health * 0.9), _state.killedMonsters + 2);
		cout << "Palying...\n";
		_state.Show();
	}

	GameMemento GameSave()
	{
		_state.Show();
		return GameMemento(_state);
	}

	void LoadGame(GameMemento memento)
	{
		_state = memento.GetState();
		_state.Show();
	}
};

class Caretaker
{
private:
	GameOriginator _game;
	vector<GameMemento> _quickSaves;

public:
	void Shoot()
	{
		_game.Play();
	}

	void F5()
	{
		if (_quickSaves.size() >= 3) cout << "No available saves!\n";
		else _quickSaves.push_back(_game.GameSave());
	}

	void F9()
	{
		if (_quickSaves.size() > 0)
		{
			_game.LoadGame(_quickSaves.back());
			_quickSaves.pop_back();
		}
	}
};

void main()
{
	Caretaker caretaker = Caretaker();

	cout << "0 - exit\n1 - Shoot\n2 - Save Game\n3 - Load Game\n----------------------------\n";
	int input = 0;
	do
	{
		cin >> input;

		switch (input)
		{
		case 1: caretaker.Shoot();	break;
		case 2: caretaker.F5();		break;
		case 3: caretaker.F9();		break;
		}

	} while (input != 0);

	system("pause");
}