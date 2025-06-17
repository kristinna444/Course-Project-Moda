#include "ViewTransactionsCommand.h"

void ViewTransactionsCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Administrator") != 0) {
		throw std::logic_error("Only the admin can view transactions");
	}

	std::cout << "All transactions made until this moment: " << std::endl;

	std::ifstream file("transactions.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = file.tellg();
	size_t numberOfTransactions = Utils::getCharOccurences(file, '\n');
	file.clear();
	file.seekg(0, currentPosition);

	for (size_t i = 0; i < numberOfTransactions; i++) {
		char buffer[CONSTANTS::MAX_LENGTH];
		file.getline(buffer, CONSTANTS::MAX_LENGTH);
		std::cout << buffer << std::endl;
	}

	file.close();

}