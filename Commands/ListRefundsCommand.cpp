#include "ListRefundsCommand.h"

void ListRefundsCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();
	std::cout << currentUser->getName() << std::endl;

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can list the refund requests!");
	}

	OrderContainer refundRequests("refund_requests.txt");
	std::cout << "Refund requests: " << std::endl;
	refundRequests.printOrders();
}