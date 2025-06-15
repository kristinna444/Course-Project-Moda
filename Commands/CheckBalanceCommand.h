#pragma once

#include "Command.h"

class CheckBalanceCommand : public Command
{
public:
	CheckBalanceCommand() = default;
	void execute(System& system) override;
};
