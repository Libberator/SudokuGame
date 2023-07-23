#include "Cell.h"

Cell::Cell() : Cell('0') {}

Cell::Cell(char element) : element(element)
{
	isClue = element != '0';
	reset();
}

bool Cell::hasValue() 
{
	return element >= '1' && element <= '9';
}

void Cell::reset()
{
	candidates = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
}
