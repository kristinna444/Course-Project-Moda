#include "RejectRefundCommand.h"

RejectRefundCommand::RejectRefundCommand(size_t ID, const MyString& description):
	ID(ID), description(description) {}

void RejectRefundCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can reject refund requests!");
	}

	OrderContainer refundRequests("refund_requests.txt");

	refundRequests[ID - 1].writeOrderToFile("rejected_requests.txt");

	std::ofstream descriptionsFile("descriptions.txt", std::ios::app);
	if (!descriptionsFile.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	descriptionsFile << description << std::endl;

	descriptionsFile.close();

	refundRequests.shiftLeft(ID - 1);
	refundRequests.updateFileWithOrders("refund_requests.txt");
}