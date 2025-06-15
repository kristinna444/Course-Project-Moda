#include "ApproveOrderCommand.h"

ApproveOrderCommand::ApproveOrderCommand(size_t ID) : ID(ID) {}  

void ApproveOrderCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can approve orders!");
	}

	OrderContainer orderContainer("orders.txt");
	orderContainer.markAsApproved(ID);

	std::cout << "Remaining pending orders: " << std::endl;
	orderContainer.listPendingOrders();
}