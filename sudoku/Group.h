#pragma once
#include "Cell.h"
#include <vector>
#include <memory>

struct Group
{
	Group();

	std::vector<std::shared_ptr<Cell>> cells;
	
	void add(std::shared_ptr<Cell> cell);
	void reset();
	bool isSolved();
};
