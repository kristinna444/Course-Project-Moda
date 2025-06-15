#include "ListOrdersCommand.h"

void ListOrdersCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can view all orders!");
	}

	OrderContainer orderContainer("orders.txt");
	orderContainer.printOrders();
}