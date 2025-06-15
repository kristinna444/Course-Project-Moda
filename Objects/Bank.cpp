#include "Bank.h"

void Bank::freeDynamicMemory()
{
	delete[] wallets;
}

void Bank::copyDynamicMemory(const Bank& other)
{
	size = other.size;
	wallets = new Wallet[size];
	for (size_t i = 0; i < size; i++) {
		wallets[i] = other.wallets[i];
	}
}

Bank::Bank()
{
	size = 1;
	wallets = new Wallet[size];
}

Bank::Bank(const Bank& other)
{
	copyDynamicMemory(other);
}

Bank& Bank::operator=(const Bank& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Wallet* Bank::getWallet(const MyString& clientEGN)
{
	for (size_t i = 0; i < size; i++) {
		if (wallets[i].getClientEGN() == clientEGN) {
			return &wallets[i];
		}
	}

	return nullptr;
}

void Bank::load()
{
	readFromFile("bank.txt");
}

void Bank::readFromFile(const char* fileName)
{
	std::ifstream input(fileName);
	if (!input.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = input.tellg();

	size = Utils::getCharOccurences(input, '\n');

	if (size == 0) {
		throw std::logic_error("There are still no clients in the system!");
	}

	delete[] wallets;
	wallets = new Wallet[size];

	input.clear();
	input.seekg(0, currentPosition);

	Wallet wallet;
	for (size_t i = 0; i < size; i++) {
		wallet.readFromFile(input);
		wallets[i] = wallet;
	}

	input.close();
}

void Bank::updateFileWithWallets()
{
	std::ofstream output("bank.txt");
	if (!output.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	for (size_t i = 0; i < size; i++) {
		wallets[i].writeToFile(output);
	}

	output.close();
}

Bank::~Bank()
{
	freeDynamicMemory();
}