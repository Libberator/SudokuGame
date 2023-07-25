#include "Group.h"
#include <list>

Group::Group() {}

void Group::add(std::shared_ptr<Cell> cell)
{
	cells.push_back(cell);
}

void Group::reset()
{
	cells.clear();
}

bool Group::isSolved()
{
	std::list<char> solvedCopy(solved, solved + std::strlen(solved));

	for (auto& cell : cells) 
	{
		if (!cell->hasValue()) return false;
		solvedCopy.remove(cell->value);
	}
	if (solvedCopy.size() == 0) return true;
	return false;
}

const char Group::solved[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };