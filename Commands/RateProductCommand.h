#pragma once

#include "Command.h"

class RateProductCommand : public Command
{
private:
	int productID;
	double rating;
public:
	RateProductCommand(int productID, double rating);
	void execute(System& system) override;
};
