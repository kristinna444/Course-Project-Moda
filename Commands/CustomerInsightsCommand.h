#pragma once

#include "Command.h"

class CustomerInsightsCommand : public Command 
{
public:
	CustomerInsightsCommand() = default;
	void execute(System& system) override;
};

