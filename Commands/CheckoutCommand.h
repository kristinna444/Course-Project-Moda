#pragma once

#include "Command.h"

class CheckoutCommand : public Command
{
public:
	CheckoutCommand() = default;
	void execute(System& system) override;
};
