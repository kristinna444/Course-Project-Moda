#include "ConfirmOrderCommand.h"

ConfirmOrderCommand::ConfirmOrderCommand(size_t ID): ID(ID) {}

void ConfirmOrderCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can confirm shipped orders!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		double loyaltyPoints = 0;

		OrderContainer orderContainer("orders.txt");
		loyaltyPoints = orderContainer.markAsConfirmed(client->getName(), ID);

		client->addPoints(loyaltyPoints);
		std::cout << "You received " << loyaltyPoints << " loyalty points." << std::endl;
	}
}