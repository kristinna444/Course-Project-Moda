#pragma once

#include "Command.h"

class ListRefundsCommand : public Command
{
public:
	ListRefundsCommand() = default;
	void execute(System& system) override;
};
