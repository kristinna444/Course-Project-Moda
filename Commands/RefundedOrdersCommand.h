#pragma once

#include "Command.h"
#include "../Objects/Mailbox.h"

class RefundedOrdersCommand : public Command
{
public:
	RefundedOrdersCommand() = default;
	void execute(System& system) override; 
};
