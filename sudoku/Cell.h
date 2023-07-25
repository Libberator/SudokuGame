#pragma once
#include <set>

class Cell
{
public:
	Cell(int row, int col, int box);
	Cell(int row, int col, int box, char value);
	
	char value;
	int row;
	int col;
	int box;
	bool isClue;
	std::set<char> candidates;

	void setValue(char val, bool isClue);
	bool hasValue();
	void reset();
};
