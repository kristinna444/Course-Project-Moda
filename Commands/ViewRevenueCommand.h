#pragma once

#include "Command.h"

class ViewRevenueCommand : public Command
{
public:
	ViewRevenueCommand() = default;
	void execute(System& system) override;
};
