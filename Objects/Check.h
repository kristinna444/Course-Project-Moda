#pragma once

#include "../MyString.h"

class Check
{
private:
	double amount;
	MyString code;
	MyString clientEGN;
	bool cashed;

public:
	Check() = default; 
	Check(double amount, const MyString& code, const MyString& clientEGN);

	double getAmount() const;
	const char* getCode() const;
	const MyString& getClientEGN() const;

	void writeCheckToFile(std::ofstream& output) const;
	void writeCheckToFile(const char* fileName) const;
	void readCheckFromFile(std::ifstream& input);

};
