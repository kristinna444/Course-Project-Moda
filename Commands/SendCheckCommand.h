#pragma once

#include "Command.h"

class SendCheckCommand : public Command
{
private:
	double amount;
	MyString code;
	MyString clientEGN;
public:
	SendCheckCommand(double amount, const MyString& code, const MyString& clientEGN);
	void execute(System& system) override;
};
