#include "RemoveFromCartCommand.h"

RemoveFromCartCommand::RemoveFromCartCommand(const MyString& productName, size_t quantity):
	productName(productName), quantity(quantity) {}

void RemoveFromCartCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can remove products from their cart!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		client->removeFromCart(productName, quantity);
	}
}