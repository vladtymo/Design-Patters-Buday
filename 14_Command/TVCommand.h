#pragma once
#include "TV.h"

class TVCommand
{
protected:
	TV* tvPlayer = nullptr;
public:
	TVCommand(TV* pTV)
	{
		tvPlayer = pTV;
	}
	virtual void Execute() = 0;
};

class TVOnCommand :public TVCommand
{
public:
	TVOnCommand(TV* ptr) :TVCommand(ptr) {}
	void Execute()
	{
		if (tvPlayer)
			tvPlayer->TurnOn();
	}
};

class TVOffCommand :public TVCommand
{
public:
	TVOffCommand(TV* ptr) :TVCommand(ptr) {}
	void Execute()
	{
		if (tvPlayer)
			tvPlayer->TurnOff();
	}
};
