#pragma once

#include "Command.h"

class ApproveOrderCommand : public Command
{
private:
	size_t ID;
public:
	ApproveOrderCommand(size_t ID); 
	void execute(System& system) override;
};
