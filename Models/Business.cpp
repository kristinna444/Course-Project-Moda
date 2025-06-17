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

void Business::help() const
{
	std::cout << "As a business you can: " << std::endl;
	std::cout << "- add and remove items" << std::endl;
	std::cout << "- manage orders and refund requests by clients by approving or rejecting them" << std::endl;
	std::cout << "- view best selling products and your revenue" << std::endl;
}

void Business::writeToFile(std::ofstream& output) const
{
	output << name << "|" << EGN << "|" << password << "|" << "Business" << std::endl;
}



