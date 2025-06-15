#include "Wallet.h"

Wallet::Wallet() : balance(0), loyaltyPoints(0) {}

Wallet::Wallet(const MyString& clientEGN) : clientEGN(clientEGN), balance(0), loyaltyPoints(0) {}

const MyString& Wallet::getClientEGN() const
{
	return clientEGN;
}

double Wallet::getBalance() const
{
	return balance;
}

double Wallet::getPoints() const
{
	return loyaltyPoints;
}

void Wallet::addMoney(double sum)
{
	balance += sum;
}

void Wallet::getSumFromWallet(double sum)
{
	if (sum > balance) {
		throw std::logic_error("Not enough money in wallet!");
	}

	balance -= sum;
}

void Wallet::addPoints(double points)
{
	loyaltyPoints += points;
}

void Wallet::setPoints(double points)
{
	if (points < 0) {
		throw std::logic_error("Points can't be a negative number!");
	}

	loyaltyPoints = points;
}

void Wallet::writeToFile(const char* fileName) const
{
	std::ofstream file(fileName, std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Program can't open file");
	}

	file << clientEGN << "|" << balance << " " << loyaltyPoints << std::endl; 

	file.close();
}

void Wallet::writeToFile(std::ofstream& output) const
{
	output << clientEGN << "|" << balance << " " << loyaltyPoints << std::endl;
}

void Wallet::readFromFile(std::ifstream& input)
{
	char EGN[CONSTANTS::MAX_LENGTH];
	input.getline(EGN, CONSTANTS::MAX_LENGTH, '|');
	this->clientEGN = MyString(EGN);

	double balance, points;
	input >> balance >> points;
	this->balance = balance;
	this->loyaltyPoints = points;

	input.ignore();
}