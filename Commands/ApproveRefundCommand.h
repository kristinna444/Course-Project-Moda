#pragma once

#include "Command.h"

class ApproveRefundCommand : public Command
{
private:
	size_t ID;
public:
	ApproveRefundCommand(size_t ID);
	void execute(System& system) override;
};
