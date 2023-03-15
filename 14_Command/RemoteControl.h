#pragma once
#include "TVCommand.h"

class RemoteControl {

private:
	TVCommand* command;
public:
	void SetCommand(TVCommand* pCommand) {
		command = pCommand;
	}
	void PressButton() {
		command->Execute();
	}
};
