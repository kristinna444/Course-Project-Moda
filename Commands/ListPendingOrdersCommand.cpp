#include "ListPendingOrdersCommand.h"

void ListPendingOrdersCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();
	std::cout << currentUser->getName() << std::endl;

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can list the pending orders!");
	}

	OrderContainer orderContainer("orders.txt");

	std::cout << "All pending orders: " << std::endl;
	orderContainer.listPendingOrders();

}