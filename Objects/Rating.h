#pragma once

#include "../MyString.h"

class Rating
{
private:
	int productID;
	MyString clientName;
	double rating;
public:
	Rating();
	Rating(int productID, const MyString& clientName, double rating);

	const MyString& getClientName() const;
	int getProductID() const;
	double getRating() const;

	void writeToFile(std::ofstream& output) const;
	void readFromFile(std::ifstream& input);
};
