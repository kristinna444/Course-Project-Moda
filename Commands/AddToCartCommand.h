#pragma once

#include "Command.h"

class AddToCartCommand : public Command
{
private:
	int productID;
	size_t quantity;

public:
	AddToCartCommand(int productID, size_t quantity);
	void execute(System& system) override;
};
