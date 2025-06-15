#include "RegisterCommand.h"

void RegisterCommand::execute(System& system)
{
	const User* currentUser = system.getCurrentUser();

	if (currentUser) {
		throw std::logic_error("Command forbidden!");
	}

	MyString name, EGN, password;
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "EGN: ";
	std::cin >> EGN;

	std::cout << "Password: ";
	std::cin >> password;

	std::cin.ignore();
	char role[CONSTANTS::MAX_LENGTH];
	std::cout << "Select a role(Administrator, Business, Client): ";
	std::cin.getline(role, CONSTANTS::MAX_LENGTH);

	system.addUser(name, EGN, password, role);
}
