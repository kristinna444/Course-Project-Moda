#pragma once

#include "Command.h"

class RemoveFromCartCommand : public Command
{
private:
	MyString productName;
	size_t quantity;
public:
	RemoveFromCartCommand(const MyString& productName, size_t quantity);
	void execute(System& system) override;
};
