#include "RemoveDiscountCommand.h"

void RemoveDiscountCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can remove the discount from their cart!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		client->removeDiscountFromCart();
	}
}