#pragma once

#include "Command.h"

class RejectRefundCommand : public Command
{
private:
	size_t ID;
	MyString description;
public:
	RejectRefundCommand(size_t ID, const MyString& description);
	void execute(System& system) override;
};
