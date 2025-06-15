#include "LoginCommand.h"

void LoginCommand::execute(System& system) 
{
	const User* currentUser = system.getCurrentUser();

	if (currentUser) {
		throw std::logic_error("Command forbidden!");
	}

	MyString name, password;
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "Password: ";
	std::cin >> password;

	User* loggedUser = system.getUserFromFile(name, password);

	if (!loggedUser) {
		throw std::logic_error("We couldn't find any user with this name or password!");
	}

	system.setCurrentUser(loggedUser);
}