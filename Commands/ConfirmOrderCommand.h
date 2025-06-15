#pragma once

#include "Command.h"

class ConfirmOrderCommand : public Command
{
private:
	size_t ID;
public:
	ConfirmOrderCommand(size_t ID);
	void execute(System& system) override;
};
