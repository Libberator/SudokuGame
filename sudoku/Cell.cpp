#include "Cell.h"

Cell::Cell(int row, int col, int box) : Cell(row, col, box, '0') {}

Cell::Cell(int row, int col, int box, char value) : row(row), col(col), box(box), value(value)
{
	isClue = value != '0';
	reset();
}

void Cell::setValue(char val, bool isClue = false)
{
	value = val;
	this->isClue = isClue && val != '0';
}

bool Cell::hasValue()
{
	return value >= '1' && value <= '9';
}

void Cell::reset()
{
	isClue = false;
	candidates = { }; // { '1', '2', '3', '4', '5', '6', '7', '8', '9'
}
