#pragma once

#include "Rating.h"
#include "../Utils.h"

class RatingContainer
{
private:
	Rating* ratings;
	size_t size; 
	size_t capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const RatingContainer& other);
	bool alreadyRated(int productID, const MyString& clientName) const;
	void shiftLeft(size_t index);
	void resize(size_t newCapacity);

public:
	RatingContainer();
	RatingContainer(const char* fileName);
	RatingContainer(const RatingContainer& other);
	RatingContainer& operator=(const RatingContainer& other);
	
	double getRating(int productID) const;
	bool addRating(int productID, const MyString& clientName, double rating); 
	bool removeRating(int productID, const MyString& clientName);

	void updateList();

	~RatingContainer();
};
