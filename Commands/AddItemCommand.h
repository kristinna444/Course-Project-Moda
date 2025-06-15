#pragma once

#include "Command.h"

class AddItemCommand : public Command
{
private:
	MyString name;
	double price;
	size_t quantity;
	MyString description;
public:
	AddItemCommand(const MyString& name, double price, size_t quantity, const MyString& description);
	void execute(System& system) override;
};
