#pragma once

#include "Command.h"

class RedeemCommand : public Command
{
private:
	MyString code;
public:
	RedeemCommand(const MyString& code);
	void execute(System& system) override;
};