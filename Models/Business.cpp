#include "Business.h"

Business::Business(const MyString& name, const MyString& EGN, const MyString& password):
	User(name, EGN, password) {}

const char* Business::getRole() const
{
	return "Business";
}

User* Business::clone() const
{
	return new Business(*this);
}

void Business::writeToFile(std::ofstream& output) const
{
	output << name << "|" << EGN << "|" << password << "|" << "Business" << std::endl;
}



