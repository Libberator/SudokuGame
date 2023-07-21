#include "SudokuGame.h"

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
    return 0;
}
