#pragma once

#include "User.h"
#include "../Storage.h"

class Business : public User
{
private:

public:
	Business(const MyString& name, const MyString& EGN, const MyString& password);

	const char* getRole() const override;

	User* clone() const override;
	void writeToFile(std::ofstream& output) const override;

};
