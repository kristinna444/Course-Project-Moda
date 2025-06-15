#include "Check.h"

Check::Check(double amount, const MyString& code, const MyString& clientEGN) :
	amount(amount), code(code), clientEGN(clientEGN), cashed(false) {}

double Check::getAmount() const
{
	return amount; 
}

const char* Check::getCode() const
{
	return code.c_str();
}

const MyString& Check::getClientEGN() const
{
	return clientEGN;
}

void Check::writeCheckToFile(std::ofstream& output) const
{
	output << amount << " " << code << " " << clientEGN << std::endl;
}

void Check::writeCheckToFile(const char* fileName) const
{
	std::ofstream output(fileName, std::ios::app);
	if (!output.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	output << amount << " " << code << " " << clientEGN << std::endl;

	output.close();
}

void Check::readCheckFromFile(std::ifstream& input)
{
	double amount;
	input >> amount;
	input.ignore();

	this->amount = amount;

	char code[CONSTANTS::MAX_LENGTH];
	input.getline(code, CONSTANTS::MAX_LENGTH, ' ');
	MyString checkCode(code);

	this->code = checkCode;

	char EGN[CONSTANTS::MAX_LENGTH];
	input.getline(EGN, CONSTANTS::MAX_LENGTH);
	MyString clientEGN(EGN);

	this->clientEGN = clientEGN; 
}