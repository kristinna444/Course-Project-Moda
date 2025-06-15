#include "RefundedOrdersCommand.h"

void RefundedOrdersCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can view their refund history!");
	}
	
	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		OrderContainer refunds("refunds.txt");

		std::cout << "All your refunded orders: " << std::endl;
		refunds.listOrdersOf(client->getName());
		
		OrderContainer rejectedRefunds("rejected_requests.txt");
		Mailbox descriptions("descriptions.txt");

		bool found = false; 
		size_t currentIndex = 1;  
		size_t numberOfRefunds = rejectedRefunds.getCurrentNumberOfOrders(); 
		
		std::cout << "Rejected refunds: " << std::endl;

		for (size_t i = 0; i < numberOfRefunds; i++) {
			if (rejectedRefunds[i].getClientName() == client->getName() &&
				strcmp(rejectedRefunds[i].getStatus(), "Delivered") == 0) {

				std::cout << currentIndex << ". ";
				rejectedRefunds[i].printOrder();
				std::cout << "Reason: " << descriptions[i] << std::endl;

				found = true;
				currentIndex++;
			}
		}

		if (!found) std::cout << "No rejected refunds on your name!" << std::endl;
	}
}