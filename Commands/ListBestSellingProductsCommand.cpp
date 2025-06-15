#include "ListBestSellingProductsCommand.h"

void ListBestSellingProductsCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can view the best selling products!");
	}

	Searchbar searchbar("items_collection.txt");
	searchbar.filterByNumberOfSales();

	bool found = false;

	std::cout << "Best selling products: " << std::endl;

	for (size_t i = 0; i < searchbar.getSize(); i++) {
		if (searchbar[i].getNumberOfSales() > 0) {
			std::cout << searchbar[i].getName() << " Sales: " << searchbar[i].getNumberOfSales() << std::endl;
			found = true;
		}
	}

	if (!found) std::cout << "No sales yet!" << std::endl;
}