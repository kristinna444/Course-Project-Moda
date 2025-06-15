#include "RequestRefundCommand.h"

void RequestRefundCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can request refunds!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		MyString clientName = client->getName();

		OrderContainer orderContainer("orders.txt");
		size_t currentNumberOfOrders = orderContainer.getCurrentNumberOfOrders();

		for (size_t i = currentNumberOfOrders; i > 0; i--) {
			if (orderContainer[i - 1].getClientName() == clientName &&
				strcmp(orderContainer[i - 1].getStatus(), "Delivered") == 0) {

				orderContainer[i - 1].writeOrderToFile("refund_requests.txt");

				return;
			}
		}

		std::cout << "No delivered orders on your name!" << std::endl;
	}
}