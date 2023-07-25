#include "Cell.h"

Cell::Cell(int row, int col, int box) : Cell(row, col, box, '0') {}

Cell::Cell(int row, int col, int box, char value) : row(row), col(col), box(box), value(value)
{
	isClue = value != '0';
	reset(false);
}

void Cell::setValue(char val, bool isClue)
{
	value = value == val ? '0' : val;
	this->isClue = isClue && val != '0';
}

bool Cell::hasValue()
{
	return value >= '1' && value <= '9';
}

void Cell::reset(bool hardReset)
{
	if (hardReset)
	{
		isClue = false;
		value = '0';
	}
	else if (!isClue)
	{
		value = '0';
	}
	candidates = { }; // { '1', '2', '3', '4', '5', '6', '7', '8', '9'
}
