#include "RemoveItemCommand.h"

RemoveItemCommand::RemoveItemCommand(const MyString& name):
	name(name) {}

void RemoveItemCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can remove items!");
	}

	Searchbar searchbar("items_collection.txt");
	int numberOfProducts = searchbar.getSize();

	for (size_t i = 0; i < numberOfProducts; i++) {
		if (searchbar[i].getStringName() == name) {
			searchbar.deleteProduct(i);
			searchbar.updateList();
			std::cout << name << " removed" << std::endl;
			return;
		}
	}

	std::cout << "We couldn't find any products with this name!" << std::endl;
}