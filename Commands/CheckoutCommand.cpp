#include "CheckoutCommand.h"

void CheckoutCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can purchase items!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		bool successful = client->checkout();

		if (successful) {
			system.deleteCart(client->getName()); 
		}
	}
}