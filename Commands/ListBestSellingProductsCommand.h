#pragma once

#include "Command.h"

class ListBestSellingProductsCommand : public Command
{
public:
	ListBestSellingProductsCommand() = default;
	void execute(System& system) override;
};
