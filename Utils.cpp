#include "Utils.h"

size_t Utils::getCharOccurences(std::stringstream& input, char ch)
{
	size_t occurs = 0; 

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

size_t Utils::getCharOccurences(std::ifstream& input, char ch)
{
	size_t occurs = 0;

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

size_t Utils::roundToPowerOfTwo(size_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}