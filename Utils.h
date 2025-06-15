#pragma once
#include <fstream>
#include <sstream>

class Utils
{
public:
	static size_t getCharOccurences(std::stringstream& input, char ch); 
	static size_t getCharOccurences(std::ifstream& input, char ch);
	static size_t roundToPowerOfTwo(size_t v);
	
};
