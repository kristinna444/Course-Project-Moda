#include "System.h"

System::System()
{
	currentUser = nullptr;
}

void System::load()
{
	users.loadUsersFromFile(); 
}

const User* System::getCurrentUser() const
{
	return currentUser;
}

User* System::getCurrentUser()
{
	return currentUser;
}

void System::setCurrentUser(User* user)
{
	currentUser = user;

	if (strcmp(currentUser->getRole(), "Client") == 0) {
		setUserData(currentUser);
	}
}

void System::setUserData(User* user)
{
	bank.load();
	carts.load();

	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		Wallet* wallet = bank.getWallet(client->getEGN());
		Cart* cart = carts.getCart(client->getName());

		if (!cart) {
			Cart newCart(client->getName());
			carts.addCart(newCart);
			cart = carts.getCart(client->getName());
		}

		client->setWallet(wallet);
		client->setCart(cart);

	}
}

User* System::getClientByName(const MyString& name)
{
	for (size_t i = 0; i < users.getNumberOfUsers(); i++) {
		if (name == users[i]->getName()) {
			return users[i];
		}
	}

	return nullptr;
}

void System::deleteCart(const MyString& clientName)
{
	carts.removeCart(clientName);
}

void System::addUser(const MyString& name, const MyString& EGN, const MyString& password, const char* role)
{
	User* newUser = UserFactory::create(name, EGN, password, role);
	users.addUser(newUser); 

	std::ofstream output("users.txt", std::ios::app); 
	if (!output.is_open()) { 
		std::cout << "Program couldn't open file" << std::endl; 
		return;
	}

	newUser->writeToFile(output);

	output.close(); 

	if (strcmp(role, "Client") == 0) {
		Wallet wallet(newUser->getEGN()); 
		wallet.writeToFile("bank.txt");
	}
}

User* System::getUserFromFile(const MyString& name, const MyString& password)
{
	users.loadUsersFromFile();

	for (size_t i = 0; i < users.getNumberOfUsers(); i++) {
		if (name == users[i]->getName() && password == users[i]->getPassword()) {
			return users[i];
		}
	}

	return nullptr;
}

void System::logout()
{
	if (Client* client = dynamic_cast<Client*>(currentUser)) {
		bank.updateFileWithWallets();
		carts.updateFileWithCarts();
	}

	delete currentUser;
	currentUser = nullptr;
}