#include "Product.h"

int Product::nextID = 0;

Product::Product(const MyString& name, double price, size_t quantity, const MyString& description) :
	name(name), price(price), quantity(quantity), numberOfSales(0), description(description), rating(0), availability(true)
{
	ID = ++nextID;
}

const char* Product::getName() const
{
	return name.c_str();
}

const MyString& Product::getStringName() const
{
	return name;
}

const char* Product::getDescription() const
{
	return description.c_str();
}

double Product::getPrice() const
{
	return price; 
}

double Product::getRating() const
{
	return rating; 
}

void Product::setRating(double rating)
{
	if (rating < 0 || rating > 5) {
		throw std::logic_error("ratings can only be between 0 and 5!");
	}

	this->rating = rating;
}

int Product::getID() const
{
	return ID;
}

size_t Product::getQuantity() const
{
	return quantity;
}

size_t Product::getNumberOfSales() const
{
	return numberOfSales;
}

void Product::writeProductToFile(std::ofstream& output) const
{
	output << ID << " " << name << "|" << price << " " << quantity << " " << numberOfSales << " " 
		<< rating << " " << description << std::endl; //chng

}

void Product::readProductFromFile(std::ifstream& input)
{
	int ID;
	input >> ID;
	this->ID = ID;

	input.ignore();

	char name[CONSTANTS::MAX_LENGTH];
	input.getline(name, CONSTANTS::MAX_LENGTH, '|');
	MyString productName(name);

	this->name = productName; 

	double price;
	size_t quantity, numberOfSales; 
	double rating; 
	input >> price >> quantity >> numberOfSales >> rating;   

	this->price = price;
	this->quantity = quantity;
	this->numberOfSales = numberOfSales;
	this->rating = rating;

	input.ignore();

	char description[CONSTANTS::MAX_LENGTH];
	input.getline(description, CONSTANTS::MAX_LENGTH);
	MyString productDescription(description);

	this->description = productDescription;
}

void Product::getProductFromStorage(size_t quantity)
{
	if (quantity > this->quantity) {
		throw std::logic_error("Not enough products!");
	}

	this->quantity -= quantity;
	numberOfSales += quantity;
}

void Product::returnProductToStorage(size_t quantity)
{
	this->quantity += quantity;
	numberOfSales -= quantity;
}

void Product::print() const
{
	std::cout << "Product #" << ID << " Name:" << name << " " << price << "BGN In stock: " << quantity << " Sold: " << numberOfSales 
		<< " Stars: " << rating << " " << description << std::endl;
}

bool operator==(const Product& lhs, const Product& rhs)
{
	return lhs.name == rhs.name;
}

bool operator!=(const Product& lhs, const Product& rhs)
{
	return !(lhs == rhs); 
}


