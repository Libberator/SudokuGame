#include "SudokuGame.h"

int main()
{
    SudokuGame game;

    while (game.isRunning()) 
    {
        game.update(game.getDeltaTime());
        game.render();
    }

    return 0;
}
