#include "RedeemCommand.h"

RedeemCommand::RedeemCommand(const MyString& code): code(code)
{
}

void RedeemCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Client") != 0) {
		throw std::logic_error("Only clients can redeem checks!");
	}

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		CheckContainer checks("uncashed_checks.txt");
		double amount = checks.getAmountFromCheck(code, client->getEGN());

		if (amount > 0) {
			client->addToWallet(amount);
			std::cout << "Successfully redeemed check. " << amount << " added to your wallet" << std::endl;

			checks.deleteCheck(code);
			checks.updateCheckList();
		}
	}
}