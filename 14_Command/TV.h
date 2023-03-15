#pragma once
#include <iostream>

class TV
{
	// power status
	bool on;
public:
	void TurnOn() {
		on = true;
		std::cout << "TV turned ON!\n";
	}
	void TurnOff() {
		on = false;
		std::cout << "TV turned OFF!\n";
	}
};
