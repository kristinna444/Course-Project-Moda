#include "CheckBalanceCommand.h"

void CheckBalanceCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can check their balance!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		client->checkBalance();
	}
}