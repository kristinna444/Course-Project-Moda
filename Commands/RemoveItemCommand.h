#pragma once

#include "Command.h"

class RemoveItemCommand : public Command
{
private:
	MyString name;
public:
	RemoveItemCommand(const MyString& name);
	void execute(System& system) override; 
};
