#include "ListShippedOrdersCommand.h"

void ListShippedOrdersCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can view their shipped orders!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		MyString clientName = client->getName();

		OrderContainer orderContainer("orders.txt");

		std::cout << "All your shipped orders: " << std::endl;
		orderContainer.listOrdersByStatus("Shipped", clientName); 
	
		OrderContainer rejectedOrders("rejected_requests.txt");
		Mailbox descriptions("descriptions.txt");

		bool found = false; 
		size_t currentIndex = 1; 
		size_t numberOfRejectedRequests = rejectedOrders.getCurrentNumberOfOrders();

		std::cout << "Rejected orders: " << std::endl;

		for (size_t i = 0; i < numberOfRejectedRequests; i++) {
			if (strcmp(rejectedOrders[i].getStatus(), "Rejected") == 0 && rejectedOrders[i].getClientName() == clientName) {
				std::cout << currentIndex << ". ";
				rejectedOrders[i].printOrder();
				std::cout << "Reason: " << descriptions[i] << std::endl;

				found = true;
				currentIndex++;
			}
		}

		if (!found) std::cout << "No rejected orders on your name!" << std::endl;
	}
}