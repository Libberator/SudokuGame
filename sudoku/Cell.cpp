#include "Cell.h"

Cell::Cell() : Cell('0') { }

Cell::Cell(char element) : element(element)
{
	candidates = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
}

bool Cell::hasValue() 
{
	return element >= '1' && element <= '9';
}