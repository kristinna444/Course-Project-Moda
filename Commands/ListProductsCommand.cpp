#include "ListProductsCommand.h"

void ListProductsCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can request to list all products!");
	}

	Searchbar searchbar("items_collection.txt");

	int option;
	std::cout << "Choose an option: " << std::endl;
	std::cout << "1 - List All Products" << std::endl;
	std::cout << "2 - Filter By Name" << std::endl;
	std::cout << "3 - Filter By Rating" << std::endl;
	std::cout << "4 - Filter By Price" << std::endl;
	std::cout << "Your choice: " << std::endl;
	std::cin >> option;
	std::cin.ignore();

	switch (option) 
	{
	case 1:
		break;
	case 2:
		searchbar.filterByNames();
		break;
	case 3:
		searchbar.filterByRatings();
		break;
	case 4:
		char order[CONSTANTS::MAX_LENGTH];
		std::cout << "ascending or descending? ";
		std::cin.getline(order, CONSTANTS::MAX_LENGTH);

		if (strcmp(order, "ascending") == 0) {
			searchbar.filterByAscendingPrice();
		}
		else if (strcmp(order, "descending") == 0) {
			searchbar.filterByDescendingPrice();
		}
		else {
			throw std::logic_error("Program couldn't understand your request");
		}
		break;
	default:
		throw std::logic_error("There's no such option!");
	}

	searchbar.print();
}