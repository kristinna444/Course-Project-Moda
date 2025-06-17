#include "ViewProfileCommand.h"

void ViewProfileCommand::execute(System& system)
{
	const User* currentUser = system.getCurrentUser();

	if (!currentUser) {
		throw std::logic_error("Command forbidden!");
	}

	currentUser->viewProfile();
}