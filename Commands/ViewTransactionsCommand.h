#pragma once

#include "Command.h"

class ViewTransactionsCommand : public Command
{
public:
	ViewTransactionsCommand() = default;
	void execute(System& system) override;

};
