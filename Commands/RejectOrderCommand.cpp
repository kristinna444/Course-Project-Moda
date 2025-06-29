#include "RejectOrderCommand.h"

RejectOrderCommand::RejectOrderCommand(size_t ID, const MyString& description): 
	ID(ID), description(description)
{
}

void RejectOrderCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can reject orders!");
	}

	OrderContainer orderContainer("orders.txt");
	Order orderToReject = orderContainer.rejectOrder(ID, description); 
	orderToReject.printOrder();

	MyString clientName = orderToReject.getClientName();
	double sumToReturn = orderToReject.getPrice();
	double pointsToReturn = (orderToReject.getDiscount() * 100);

	User* user = system.getClientByName(clientName);
	system.transaction(user->getEGN(), sumToReturn, pointsToReturn);

}