#pragma once

#include "User.h"
#include "../Objects/Check.h" 

class Administrator : public User
{
public:
	Administrator(const MyString& name, const MyString& EGN, const MyString& password);

	const char* getRole() const override;

	User* clone() const override;
	void writeToFile(std::ofstream& output) const override;

};
