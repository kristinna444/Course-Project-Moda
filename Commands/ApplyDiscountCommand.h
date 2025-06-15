#pragma once

#include "Command.h"

class ApplyDiscountCommand : public Command
{
public:
	ApplyDiscountCommand() = default;
	void execute(System& system) override;
};
