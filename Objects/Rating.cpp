#include "Rating.h"

Rating::Rating(): productID(0), rating(1)
{
}

Rating::Rating(int productID, const MyString& clientName, double rating):
	productID(productID), clientName(clientName)
{
	if (rating < 0 || rating > 5) {
		throw std::logic_error("Rating must be between 0 and 5");
	}

	this->rating = rating;
}

const MyString& Rating::getClientName() const
{
	return clientName;
}

int Rating::getProductID() const
{
	return productID;
}

double Rating::getRating() const
{
	return rating;
}

void Rating::writeToFile(std::ofstream& output) const
{
	output << productID << "-" << clientName << "-" << rating << std::endl;
}

void Rating::readFromFile(std::ifstream& input)
{
	int productID;
	input >> productID;
	this->productID = productID;

	input.ignore();

	char name[CONSTANTS::MAX_LENGTH];
	input.getline(name, CONSTANTS::MAX_LENGTH, '-');
	clientName = MyString(name);

	double rating;
	input >> rating;

	if (rating < 0 || rating > 5) {
		throw std::logic_error("Rating must be between 0 and 5");
	}

	this->rating = rating;

	input.ignore();
}