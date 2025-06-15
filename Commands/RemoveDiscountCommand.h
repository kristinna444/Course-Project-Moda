#pragma once

#include "Command.h"

class RemoveDiscountCommand : public Command
{
public:
	RemoveDiscountCommand() = default;
	void execute(System& system) override;
};
