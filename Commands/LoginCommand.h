#pragma once

#include "Command.h"
#include <sstream>

class LoginCommand : public Command
{
public:
	LoginCommand() = default;
	void execute(System& system) override;
};
