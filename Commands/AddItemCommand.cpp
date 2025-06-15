#include "AddItemCommand.h"

AddItemCommand::AddItemCommand(const MyString& name, double price, size_t quantity, const MyString& description):
	name(name), price(price), quantity(quantity), description(description)
{
}

void AddItemCommand::execute(System& system)
{
	User* currentUser = system.getCurrentUser();

	if (!currentUser || strcmp(currentUser->getRole(), "Business") != 0) {
		throw std::logic_error("Only the seller can add items!");
	}

	Product newProduct(name, price, quantity, description);

	std::ofstream output("items_collection.txt", std::ios::app);
	if (!output.is_open()) {
		std::cout << "Program couldn't open file" << std::endl;
	}

	newProduct.writeProductToFile(output);

	output.close();
}