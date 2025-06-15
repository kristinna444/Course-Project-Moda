#include "RatingContainer.h"

void RatingContainer::freeDynamicMemory()
{
	delete[] ratings;
}

void RatingContainer::copyDynamicMemory(const RatingContainer& other)
{
	size = other.size;
	capacity = other.capacity;

	ratings = new Rating[capacity];

	for (size_t i = 0; i < size; i++) {
		ratings[i] = other.ratings[i];
	}
}

bool RatingContainer::alreadyRated(int productID, const MyString& clientName) const
{
	for (size_t i = 0; i < size; i++) {
		if (ratings[i].getProductID() == productID && ratings[i].getClientName() == clientName) {
			return true;
		}
	}

	return false;
}

void RatingContainer::shiftLeft(size_t index)
{
	for (size_t i = index; i < size - 1; i++) {
		ratings[i] = ratings[i + 1];
	}
}

void RatingContainer::resize(size_t newCapacity)
{
	capacity = newCapacity;

	Rating* temp = new Rating[capacity];
	for (size_t i = 0; i < size; i++) {
		temp[i] = ratings[i];
	}

	delete[] ratings;
	ratings = temp;
}

RatingContainer::RatingContainer(): size(0), capacity(CONSTANTS::BEG_CAPACITY)
{
	ratings = new Rating[capacity];
}

RatingContainer::RatingContainer(const char* fileName):
	size(0), capacity(0), ratings(nullptr)
{
	std::ifstream input(fileName);
	if (!input.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = input.tellg();

	delete[] ratings;
	size = Utils::getCharOccurences(input, '\n'); 

	input.clear(); 
	input.seekg(0, currentPosition);
	
	if (size == 0) {
		capacity = CONSTANTS::BEG_CAPACITY;
		ratings = new Rating[capacity];

	}
	else {
		capacity = Utils::roundToPowerOfTwo(size);
		ratings = new Rating[capacity];

		Rating rating; 
		for (size_t i = 0; i < size; i++) { 
			rating.readFromFile(input);
			ratings[i] = rating;
		}
	}

	input.close();
}

RatingContainer::RatingContainer(const RatingContainer& other)
{
	copyDynamicMemory(other);
}

RatingContainer& RatingContainer::operator=(const RatingContainer& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

double RatingContainer::getRating(int productID) const
{
	size_t counter = 0;
	double sumOfRatings = 0;

	for (size_t i = 0; i < size; i++) {
		if (ratings[i].getProductID() == productID) {
			sumOfRatings += ratings[i].getRating();
			counter++;
		}
	}

	if (counter == 0) return 0;

	std::cout << sumOfRatings << std::endl;
	std::cout << counter << std::endl;
	return sumOfRatings / counter;
}

bool RatingContainer::addRating(int productID, const MyString& clientName, double rating)
{
	if (alreadyRated(productID, clientName)) {
		std::cout << "You have already rated this product!" << std::endl;
		return false;
	}

	if (size == capacity) {
		resize(capacity * CONSTANTS::RES_FACTOR);
	}
	
	ratings[size++] = Rating(productID, clientName, rating);
	std::cout << clientName << "'s review on product #" << productID << " was added." << std::endl;

	return true;
}

bool RatingContainer::removeRating(int productID, const MyString& clientName)
{
	for (size_t i = 0; i < size; i++) {
		if (ratings[i].getProductID() == productID && ratings[i].getClientName() == clientName) {
			shiftLeft(i);
			size--;

			std::cout << clientName << "'s review on product #" << productID << " was removed." << std::endl;
			return true;
		}
	}

	std::cout << "Sorry! We couldn't find any reviews on this product from that client." << std::endl;
	return false;
}

void RatingContainer::updateList()
{
	std::ofstream ratingsFile("ratings.txt");

	if (!ratingsFile.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	for (size_t i = 0; i < size; i++) {
		ratings[i].writeToFile(ratingsFile);
	}

	ratingsFile.close();
}

RatingContainer::~RatingContainer()
{
	freeDynamicMemory();
}