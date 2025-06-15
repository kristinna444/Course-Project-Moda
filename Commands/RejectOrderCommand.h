#pragma once

#include "Command.h"

class RejectOrderCommand : public Command
{
private:
	size_t ID;
	MyString description;
public:
	RejectOrderCommand(size_t ID, const MyString& description);
	void execute(System& system) override;

};
