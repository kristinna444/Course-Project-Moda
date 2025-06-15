#include "AddToCartCommand.h"

AddToCartCommand::AddToCartCommand(int productID, size_t quantity):
	productID(productID), quantity(quantity) {}

void AddToCartCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can add to their cart!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		client->addToCart(productID, quantity);
	}
}