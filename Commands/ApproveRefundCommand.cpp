#include "ApproveRefundCommand.h"

ApproveRefundCommand::ApproveRefundCommand(size_t ID): ID(ID) {}

void ApproveRefundCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can approve refunds!");
	}

	OrderContainer orderContainer("orders.txt");
	OrderContainer refundRequests("refund_requests.txt");

	if (ID > refundRequests.getCurrentNumberOfOrders()) {
		throw std::out_of_range("There's no request with this ID!");
	}

	MyString clientName = refundRequests[ID - 1].getClientName();
	double sumToRefund = refundRequests[ID - 1].getPrice();

	refundRequests[ID - 1].returnProductsToStorage();

	orderContainer.deleteOrder(refundRequests[ID - 1]);
	orderContainer.updateFileWithOrders("orders.txt");

	Order deletedOrder = refundRequests[ID - 1]; 

	refundRequests[ID - 1].setStatus("Refunded"); 
	refundRequests[ID - 1].writeOrderToFile("refunds.txt"); 

	refundRequests.shiftLeft(ID - 1); 
	refundRequests.updateFileWithOrders("refund_requests.txt"); 

	RatingContainer ratings("ratings.txt");
	Searchbar searchbar("items_collection.txt");

	size_t productQuantity = 0;
	for (size_t i = 0; i < deletedOrder.getSize(); i += productQuantity) { 
		Product currentProduct = deletedOrder[i]; 
		MyString currentName = currentProduct.getStringName();
		int currentID = currentProduct.getID();

		productQuantity = deletedOrder.getProductQuantity(currentName);  

		if (!orderContainer.hasProduct(clientName, currentID)) {
			bool successful = ratings.removeRating(currentID, clientName); 

			if (successful) {
				ratings.updateList();
				double newRating = ratings.getRating(currentID); 

				searchbar.rateProduct(currentID, newRating);
				searchbar.updateList();
			}
		}
	}
	
	User* user = system.getClientByName(clientName);
	if (Client* client = dynamic_cast<Client*>(user)) {
		client->addToWallet(sumToRefund);
		client->setPointsToZero();
	}
}