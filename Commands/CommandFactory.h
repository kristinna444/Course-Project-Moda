#pragma once

#include "Command.h"

class CommandFactory
{
public:
	static Command* create(const char* input);
};
