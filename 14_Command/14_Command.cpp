#include <iostream>
#include "RemoteControl.h"
using namespace std;

int main()
{
	RemoteControl control;
	TV* myTV = new TV();

	TVCommand* tvOn = new TVOnCommand(myTV);
	TVCommand* tvOff = new TVOffCommand(myTV);

	// execute ON command
	control.SetCommand(tvOn);
	control.PressButton();

	// execute OFF command
	control.SetCommand(tvOff);
	control.PressButton();

	delete tvOff;
	delete tvOn;
	delete myTV;

	system("pause");
	return 0;
}