#include "RateProductCommand.h"

RateProductCommand::RateProductCommand(int productID, double rating):
	productID(productID), rating(rating)
{
}

void RateProductCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can rate products!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		OrderContainer orders("orders.txt");

		bool found = orders.hasProduct(client->getName(), productID);

		if (!found) {
			std::cout << "We couldn't find any orders with this product on your name!" << std::endl;
			return;
		}
		
		RatingContainer ratings("ratings.txt");
		bool rated = ratings.addRating(productID, client->getName(), rating);

		if (rated) {
			ratings.updateList(); 
			double newRating = ratings.getRating(productID);

			Searchbar searchbar("items_collection.txt");

			searchbar.rateProduct(productID, newRating); 
			searchbar.updateList();
		}
	}
}