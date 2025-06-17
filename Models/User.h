#pragma once

#include "../MyString.h"

class User
{
protected:
	MyString name;
	MyString EGN;
	MyString password;

public:
	User() = default; 
	User(const MyString& name, const MyString& EGN, const MyString& password);

	const MyString& getName() const;
	const MyString& getPassword() const;
	const MyString& getEGN() const;

	virtual const char* getRole() const = 0;
	virtual void help() const = 0;
	void viewProfile() const;

	virtual User* clone() const = 0;
	virtual void writeToFile(std::ofstream& output) const = 0;

	virtual ~User() = default;
};
