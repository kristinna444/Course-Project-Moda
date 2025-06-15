#include "Storage.h"

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
}

Product* Storage::readProductsFromFile(const char* fileName, int& numberOfProducts)
{
	std::ifstream input(fileName);
	if (!input.is_open()) {
		std::cout << "Program couldn't open this file!" << std::endl;
		return nullptr;
	}

	numberOfProducts = getCharOccurences(input, '\n');
	Product* temp = new Product[numberOfProducts];

	input.clear();
	input.seekg(0, std::ios::beg);

	Product product;
	for (int i = 0; i < numberOfProducts; i++) {
		product.readProductFromFile(input);
		temp[i] = product;
	}

	input.close();

	return temp;
}

Product* Storage::getProductByName(Product* products, size_t size, const MyString& productName)
{
	for (size_t i = 0; i < size; i++) {
		if (productName == products[i].getStringName()) {
			return &products[i];
		}
	}

	throw std::logic_error("No product with this name");
}

void Storage::updateList(const Product* products, int size, const char* fileName)
{
	std::ofstream output(fileName); 
	if (!output.is_open()) { 
		std::cout << "Program couldn't open file" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++) { 
		products[i].writeProductToFile(output); 
	}

	output.close(); 
}

Product Storage::getProductByName(const char* productName)
{
	int numberOfProducts = 0;
	Product* products = readProductsFromFile("items_collection.txt", numberOfProducts);

	for (int i = 0; i < numberOfProducts; i++) {
		if (strcmp(productName, products[i].getName()) == 0) {
			Product desiredProduct = products[i];
			delete[] products;
			return desiredProduct; 
		}
	}

	throw std::logic_error("No product with this name");
}
