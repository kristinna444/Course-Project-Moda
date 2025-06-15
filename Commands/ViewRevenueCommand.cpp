#include "ViewRevenueCommand.h"

void ViewRevenueCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can view their revenue!");
	}

	OrderContainer orderContainer("orders.txt");

	double revenue = 0; 
	size_t currentNumberOfOrders = orderContainer.getCurrentNumberOfOrders();
	
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orderContainer[i].getStatus(), "Delivered") == 0 ||
			strcmp(orderContainer[i].getStatus(), "Shipped") == 0) {
			revenue += orderContainer[i].getPrice();
		}
	}

	std::cout << "Your revenue: " << revenue << "BGN" << std::endl;
}
