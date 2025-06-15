#pragma once

#include "Wallet.h"
#include "../Utils.h"

class Bank
{
private:
	Wallet* wallets;
	size_t size;

	void freeDynamicMemory();
	void copyDynamicMemory(const Bank& other);

public:
	Bank();
	Bank(const Bank& other);
	Bank& operator=(const Bank& other);

	Wallet* getWallet(const MyString& clientEGN);

	void load();
	void readFromFile(const char* fileName);
	void updateFileWithWallets();

	~Bank();
};
