#include "ViewProductCommand.h"

ViewProductCommand::ViewProductCommand(int productID): productID(productID)
{
}

void ViewProductCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can request to view a specific product!");
	}

	Searchbar searchbar("items_collection.txt");
	searchbar.viewProduct(productID); 
}