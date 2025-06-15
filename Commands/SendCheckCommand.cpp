#include "SendCheckCommand.h"

SendCheckCommand::SendCheckCommand(double amount, const MyString& code, const MyString& clientEGN):
	amount(amount), code(code), clientEGN(clientEGN)
{
}

void SendCheckCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Administrator") != 0) {
		throw std::logic_error("Only the admin can send checks");
	}

	CheckContainer checks("uncashed_checks.txt");
	bool exists = checks.hasCheck(code);

	while (exists) {
		char buffer[CONSTANTS::BEG_CAPACITY];
		std::cout << "The check code must be unique! New code: ";
		std::cin.getline(buffer, CONSTANTS::MAX_LENGTH);
		this->code = MyString(buffer);

		exists = checks.hasCheck(code);
	}

	Check newCheck(amount, code, clientEGN);
	newCheck.writeCheckToFile("uncashed_checks.txt");

	std::ofstream file("transactions.txt", std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	file << "Check to: " << clientEGN << ", Amount: " << amount << std::endl;

	file.close();
}