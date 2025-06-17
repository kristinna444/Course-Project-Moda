#include "Client.h"

Client::Client(const MyString& name, const MyString& EGN, const MyString& password):
	User(name, EGN, password), wallet(nullptr), cart(nullptr) {}

void Client::setWallet(Wallet* wallet)
{
	this->wallet = wallet;
}

void Client::setCart(Cart* cart)
{
	this->cart = cart;
}

const char* Client::getRole() const
{
	return "Client";
}

void Client::help() const
{
	std::cout << "As a client you can: " << std::endl;
	std::cout << "- view all available products" << std::endl;
	std::cout << "- manage your cart by adding and removing items" << std::endl;
	std::cout << "- manage your wallet by using discounts" << std::endl;
	std::cout << "- make, confirm and refund orders" << std::endl;
	std::cout << "- rate products" << std::endl;
}

User* Client::clone() const
{
	return new Client(*this);
}

void Client::writeToFile(std::ofstream& output) const
{
	output << name << "|" << EGN << "|" << password << "|" << "Client" << std::endl;
}

void Client::checkBalance() const
{
	std::cout << "Current balance: " << wallet->getBalance() << " BGN" << std::endl;
	std::cout << "Loyalty points: " << wallet->getPoints() << std::endl;
}

void Client::addPoints(double points)
{
	wallet->addPoints(points);
}

void Client::addToWallet(double sum)
{
	wallet->addMoney(sum); 
}

void Client::setPointsToZero()
{
	wallet->setPoints(0);
}

void Client::loadSearchbar()
{
	searchbar.load();
	isSearchbarLoaded = true;
}

void Client::addToCart(int productID, size_t quantity)
{
	if (!isSearchbarLoaded) {
		searchbar.load(); 
	}
	
	Product newProduct = searchbar.getProduct(productID, quantity); 
	for (size_t i = 0; i < quantity; i++) {
		cart->addProduct(newProduct);  
	}
		
	std::cout << quantity << "x " << newProduct.getName() << " added to your cart" << std::endl;
	
}

void Client::removeFromCart(const MyString& productName, size_t quantity)
{
	cart->removeProduct(productName, quantity); 
}

void Client::viewCart() const 
{
	cart->view();  
}

void Client::applyDiscountToCart()
{
	double points = wallet->getPoints();
	double discount = points * 0.01; 
	bool successful = cart->applyDiscount(discount); 

	if (!successful) {
		std::cout << "Points stay the same." << std::endl;
		return;
	}

	std::cout << "Discount successfully applied! " << discount << " off your order!" << std::endl;
	wallet->setPoints(0);
}

void Client::removeDiscountFromCart()
{
	double sum = cart->removeDiscount(); 

	if (sum == 0) {
		std::cout << "Points stay the same." << std::endl;
		return;
	}

	wallet->addPoints(sum * 100);
	std::cout << "Discount successfully removed! " << (sum * 100) << " points received" << std::endl; 
}

bool Client::checkout()
{
	double amount = cart->getTotalAmount();  
	if (wallet->getBalance() < amount) {
		std::cout << "You don't have enough money in your wallet!" << std::endl;
		return false;
	}

	wallet->getSumFromWallet(amount); 

	Order newOrder(cart->getProducts(), cart->getSize(), amount, cart->getDiscount(), MyString("Pending"), name);  
	newOrder.writeOrderToFile("orders.txt");

	cart->empty(); 

	std::ofstream file("transactions.txt", std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Program couldn't open file!");
	}

	file << "New purchase from: " << name << " Amount: " << amount << std::endl;

	file.close();
	return true;
}