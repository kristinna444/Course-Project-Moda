#pragma once

#include "Command.h"

class ListProductsCommand : public Command
{
public:
	ListProductsCommand() = default;
	void execute(System& system) override;
};
