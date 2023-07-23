#pragma once
#include <set>

class Cell
{
public:
	Cell();
	Cell(char element);
	
	char element;
	bool isClue;
	std::set<char> candidates;

	bool hasValue();
	void reset();
};
