#pragma once

#include "Command.h"
#include "../Objects/Mailbox.h"

class ListShippedOrdersCommand : public Command
{
public:
	ListShippedOrdersCommand() = default;
	void execute(System& system) override;
};