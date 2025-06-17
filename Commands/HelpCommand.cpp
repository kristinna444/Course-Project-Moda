#include "HelpCommand.h"

void HelpCommand::execute(System& system)
{
	const User* currentUser = system.getCurrentUser();

	if (!currentUser) {
		throw std::logic_error("Command forbidden!");
	}

	currentUser->help();
}