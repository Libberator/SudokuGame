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

    //std::vector<std::reference_wrapper<Cell>> group;

    //for (char i = '1'; i <= '9'; i++)
    //{
    //    Cell cell(i);
    //    std::cout << "Adding " << i << std::endl;

    //    group.push_back(std::ref(cell));
    //}

    //std::cout << group[2].get().hasValue() << std::endl;
    //group[2].get().element = '0';
    //std::cout << group[2].get().hasValue() << std::endl;

    /*group.reset();
    std::cout << group.isSolved() << std::endl;
    group2.cells[8]->element = '9';
    std::cout << group2.isSolved() << std::endl;*/

    return 0;
}
