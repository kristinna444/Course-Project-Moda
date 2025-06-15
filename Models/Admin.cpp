#include "Admin.h"

Administrator::Administrator(const MyString& name, const MyString& EGN, const MyString& password):
	User(name, EGN, password) {}

const char* Administrator::getRole() const
{
	return "Administrator";
}

User* Administrator::clone() const
{
	return new Administrator(*this);
}

void Administrator::writeToFile(std::ofstream& output) const
{
	output << name << "|" << EGN << "|" << password << "|" << "Administrator" << std::endl;
}