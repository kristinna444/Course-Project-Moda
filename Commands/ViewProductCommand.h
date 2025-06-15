#pragma once

#include "Command.h"

class ViewProductCommand : public Command
{
private:
	int productID;

public:
	ViewProductCommand(int productID);
	void execute(System& system) override;
};
