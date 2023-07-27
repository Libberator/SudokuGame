#pragma once
#include <set>

struct Cell
{
	Cell(int col, int row, int box);
	Cell(int col, int row, int box, char value);
	
	char value;
	int col;
	int row;
	int box;
	bool isClue;
	std::set<char> candidates;

	void setValue(char val, bool isClue);
	bool hasValue();
	void reset(bool hardReset);
};
