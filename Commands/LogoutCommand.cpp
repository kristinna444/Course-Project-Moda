#include "LogoutCommand.h"

void LogoutCommand::execute(System& system)
{
	const User* currentUser = system.getCurrentUser();

	if (!currentUser) {
		throw std::logic_error("Command forbidden!");
	}

	system.logout();
}