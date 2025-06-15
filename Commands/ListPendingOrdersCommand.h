#pragma once

#include "Command.h"

class ListPendingOrdersCommand : public Command
{
public:
	ListPendingOrdersCommand() = default;
	void execute(System& system) override;
};
