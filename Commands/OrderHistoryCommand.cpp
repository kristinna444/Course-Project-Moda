#include "OrderHistoryCommand.h"

void OrderHistoryCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can view their order history!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		MyString clientName = client->getName();

		OrderContainer orderContainer("orders.txt");

		std::cout << "All your delivered orders: " << std::endl;
		orderContainer.listOrdersByStatus("Delivered", clientName);
	}
}