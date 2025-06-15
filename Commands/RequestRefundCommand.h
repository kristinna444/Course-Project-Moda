#pragma once

#include "Command.h"

class RequestRefundCommand : public Command
{
public:
	RequestRefundCommand() = default;
	void execute(System& system) override;
};
