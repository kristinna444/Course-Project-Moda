#pragma once

#include "Command.h"

class ViewCartCommand : public Command
{
public:
	ViewCartCommand() = default;
	void execute(System& system) override;
};
