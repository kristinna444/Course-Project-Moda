#include "Admin.h"

Administrator::Administrator(const MyString& name, const MyString& EGN, const MyString& password):
	User(name, EGN, password) {}

const char* Administrator::getRole() const
{
	return "Administrator";
}

void Administrator::help() const
{
	std::cout << "As an administrator you can: " << std::endl;
	std::cout << "- send checks to clients" << std::endl;
	std::cout << "- view statistics about clients" << std::endl;
	std::cout << "- view all transactions made" << std::endl;
}

User* Administrator::clone() const
{
	return new Administrator(*this);
}

void Administrator::writeToFile(std::ofstream& output) const
{
	output << name << "|" << EGN << "|" << password << "|" << "Administrator" << std::endl;
}