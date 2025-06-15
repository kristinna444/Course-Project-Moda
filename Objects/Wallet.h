#pragma once

#include "../MyString.h"

class Wallet
{
private:
	MyString clientEGN;
	double balance;
	double loyaltyPoints;
public:
	Wallet();
	Wallet(const MyString& clientEGN);

	const MyString& getClientEGN() const;

	double getBalance() const;
	double getPoints() const;

	void addMoney(double sum);
	void getSumFromWallet(double sum);

	void addPoints(double points);
	void setPoints(double points);

	void writeToFile(const char* fileName) const;
	void writeToFile(std::ofstream& output) const;
	void readFromFile(std::ifstream& input);
};
