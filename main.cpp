#include "SudokuGame.h"
#include "Cell.h"
#include "Group.h"
#include <iostream>

int main()
{
    SudokuGame game;
    float deltaTime;

    while (game.isRunning()) 
    {
        deltaTime = game.getDeltaTime();
        game.update(deltaTime);
        game.render();
    }

   /* Group group;
    Group group2;

    for (char i = '1'; i <= '9'; i++)
    {
        std::shared_ptr<Cell> sharedCell = std::make_shared<Cell>();
        sharedCell->element = i;
        std::cout << "Adding " << i << std::endl;

        group.add(sharedCell);
        group2.add(sharedCell);
    }

    std::cout << group.isSolved() << std::endl;
    group.cells[8]->element = '0';
    std::cout << group2.isSolved() << std::endl;
    group.reset();
    std::cout << group.isSolved() << std::endl;
    group2.cells[8]->element = '9';
    std::cout << group2.isSolved() << std::endl;*/

    return 0;
}
