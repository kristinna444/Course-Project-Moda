#include "Searchbar.h"

namespace {
	int getCharOccurences(std::ifstream& input, char ch) {
		int occurs = 0;

		while (true) {
			char current = input.get();

			if (input.eof()) {
				return occurs;
			}

			if (current == ch) {
				occurs++;
			}
		}
	}
} //change

void Searchbar::freeDynamicMemory()
{
	delete[] products;
}

void Searchbar::copyDynamicMemory(const Searchbar& other)
{
	size = other.size;
	capacity = other.capacity;

	products = new Product[capacity];

	for (size_t i = 0; i < size; i++) {
		products = other.products;
	}
}

void Searchbar::moveDynamicMemory(Searchbar&& other)
{
	products = other.products;
	other.products = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void Searchbar::shiftLeft(size_t index)
{
	for (size_t i = index; i < size - 1; i++) {
		products[i] = products[i + 1];
	}
}

void Searchbar::resize(int newCapacity)
{
	capacity = newCapacity;

	Product* temp = new Product[capacity];

	for (size_t i = 0; i < size; i++) {
		temp[i] = products[i];
	}

	delete[] products;
	products = temp;
}

void Searchbar::swapProducts(Product& lhs, Product& rhs)
{
	Product temp = lhs;
	lhs = rhs;
	rhs = temp; 
}

Searchbar::Searchbar():size(0), capacity(CONSTANTS::BEG_CAPACITY)
{
	products = new Product[capacity];
}

Searchbar::Searchbar(const char* fileName): size(0), capacity(0), products(nullptr)
{
	std::ifstream input(fileName);
	if (!input.is_open()) {
		throw std::runtime_error("Program couldn't open this file");
	}

	delete[] products;
	capacity = getCharOccurences(input, '\n');
	products = new Product[capacity]; 

	input.clear();
	input.seekg(0, std::ios::beg);

	Product product;
	for (int i = 0; i < capacity; i++) {
		product.readProductFromFile(input);
		products[size++] = product;
	}

	input.close();
}//change

Searchbar::Searchbar(const Searchbar& other)
{
	copyDynamicMemory(other);
}

Searchbar& Searchbar::operator=(const Searchbar& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Searchbar::Searchbar(Searchbar&& other) noexcept
{
	moveDynamicMemory(std::move(other));
}

Searchbar& Searchbar::operator=(Searchbar&& other) noexcept
{
	if (this != &other) {
		freeDynamicMemory();
		moveDynamicMemory(std::move(other));
	}

	return *this;
}

const Product& Searchbar::operator[](size_t index) const
{
	return products[index];
}

Product& Searchbar::operator[](size_t index)
{
	return products[index];
}

int Searchbar::getSize() const
{
	return size; 
}

void Searchbar::load()
{
	int numberOfProducts = 0;

	delete[] products;
	products = Storage::readProductsFromFile("items_collection.txt", numberOfProducts);

	size = numberOfProducts;
	capacity = Utils::roundToPowerOfTwo(numberOfProducts); 
}

void Searchbar::listProducts()
{
	for (int i = 0; i < size; i++) {
		std::cout << i + 1 << " " << products[i].getName() << " " << products[i].getPrice() << " BGN "
			<< products[i].getRating() << " rating " << products[i].getQuantity() << " quantity" << std::endl;
	}
}

void Searchbar::filterByNumberOfSales()
{
	for (size_t i = 0; i < size; i++) {
		size_t maxIndex = i;
		for (size_t j = i + 1; j < size; j++) {
			if (products[maxIndex].getNumberOfSales() < products[j].getNumberOfSales()) { 
				maxIndex = j;
			}
		}

		if (maxIndex != i) { 
			swapProducts(products[maxIndex], products[i]); 
		}
	}
}

void Searchbar::filterByRatings()
{
	for (size_t i = 0; i < size; i++) {
		size_t maxIndex = i;
		for (size_t j = i + 1; j < size; j++) {
			if (products[maxIndex].getRating() < products[j].getRating()) { 
				maxIndex = j;
			}
		}

		if (maxIndex != i) {
			swapProducts(products[maxIndex], products[i]);
		}
	}
}

void Searchbar::filterByNames()
{
	for (size_t i = 0; i < size; i++) {
		size_t currentIndex = i;
		for (size_t j = i + 1; j < size; j++) {
			if (strcmp(products[currentIndex].getName(), products[j].getName()) > 0) {
				currentIndex = j;
			}
		}

		if (currentIndex != i) {
			swapProducts(products[currentIndex], products[i]);
		}
	}
}

void Searchbar::filterByAscendingPrice()
{
	for (size_t i = 0; i < size; i++) { 
		size_t minIndex = i; 
		for (size_t j = i + 1; j < size; j++) {
			if (products[minIndex].getPrice() > products[j].getPrice()) { 
				minIndex = j; 
			}
		}

		if (minIndex != i) { 
			swapProducts(products[minIndex], products[i]); 
		}
	}
}

void Searchbar::filterByDescendingPrice()
{
	for (size_t i = 0; i < size; i++) { 
		size_t maxIndex = i; 
		for (size_t j = i + 1; j < size; j++) { 
			if (products[maxIndex].getPrice() < products[j].getPrice()) {
				maxIndex = j; 
			}
		}

		if (maxIndex != i) { 
			swapProducts(products[maxIndex], products[i]); 
		}
	}
}

void Searchbar::viewProduct(int productID) const
{
	for (size_t i = 0; i < size; i++) {
		if (products[i].getID() == productID) {
			std::cout << "Name: " << products[i].getName() << std::endl;
			std::cout << "Price: " << products[i].getPrice() << std::endl;
			std::cout << "In stock: " << products[i].getQuantity() << std::endl;
			std::cout << "Rating: " << products[i].getRating() << std::endl;
			std::cout << "Description: " << products[i].getDescription() << std::endl;
			return;
		}
	}

	std::cout << "There's no such product!" << std::endl;
}

void Searchbar::print() const
{
	for (size_t i = 0; i < size; i++) {
		products[i].print();
	}
}

const Product& Searchbar::getProduct(int productID, size_t quantity) const
{
	for (size_t i = 0; i < size; i++) {
		if (products[i].getID() == productID && quantity <= products[i].getQuantity()) {
			return products[i];
		}
	}

	throw std::logic_error("No products with this ID in storage!");
}

void Searchbar::deleteProduct(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("index out of range!");
	}

	shiftLeft(index);
	size--;
}

void Searchbar::rateProduct(int productID, double rating)
{
	for (size_t i = 0; i < size; i++) {
		if (products[i].getID() == productID) {
			products[i].setRating(rating);
			std::cout << products[i].getRating() << std::endl;
			products[i].print();
			return;
		}
	}

	std::cout << "Couldn't find product!" << std::endl;
}

void Searchbar::updateList() const
{
	std::ofstream output("items_collection.txt");
	if (!output.is_open()) {
		std::cout << "Program couldn't open file" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++) {
		products[i].writeProductToFile(output);
	}

	output.close();
}

Searchbar::~Searchbar()
{
	freeDynamicMemory();
}