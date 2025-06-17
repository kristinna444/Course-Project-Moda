#include "CustomerInsightsCommand.h"

void CustomerInsightsCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Administrator") != 0) {
		throw std::logic_error("Only the admin can send checks");
	}

	std::cout << "Customer insights: " << std::endl;

	OrderContainer orderContainer("orders.txt");
	const User* user;
	for (size_t i = 0; i < system.getNumberOfUsers(); i++) {
		user = system.getUser(i);
		if (strcmp(user->getRole(), "Client") == 0) {
			std::cout << user->getName() << ": ";
			std::cout << orderContainer.numberOfCompletedOrders(user->getName()) << " completed purchases, ";
			std::cout << orderContainer.totalAmountSpent(user->getName()) << " money spent" << std::endl;
		}
	}
}