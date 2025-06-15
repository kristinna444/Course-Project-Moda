#pragma once

#include "Command.h"

class RegisterCommand : public Command
{
public:
	RegisterCommand() = default;
	void execute(System& system) override;
};
