#pragma once
#include <set>

class Cell
{
public:
	Cell();
	Cell(char element);
	
	char element;
	std::set<char> candidates;

	bool hasValue();
};
