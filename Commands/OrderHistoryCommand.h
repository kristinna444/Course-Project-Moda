#pragma once

#include "Command.h"

class OrderHistoryCommand : public Command
{
public:
	OrderHistoryCommand() = default;
	void execute(System& system) override;
};
