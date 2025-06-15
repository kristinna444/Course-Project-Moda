#include "User.h"

User::User(const MyString& name, const MyString& EGN, const MyString& password) :
	name(name), EGN(EGN), password(password) {}

const MyString& User::getName() const
{
	return name;
}

const MyString& User::getPassword() const
{
	return password;
}

const MyString& User::getEGN() const
{
	return EGN;
}