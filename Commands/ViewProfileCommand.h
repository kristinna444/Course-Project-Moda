#pragma once

#include "Command.h"

class ViewProfileCommand : public Command
{
public:
	ViewProfileCommand() = default;
	void execute(System& system) override;
};