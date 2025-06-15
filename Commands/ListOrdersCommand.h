#pragma once

#include "Command.h"

class ListOrdersCommand : public Command
{
public:
	ListOrdersCommand() = default;
	void execute(System& system) override;
};
