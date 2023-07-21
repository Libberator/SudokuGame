#include "SudokuGame.h"

int main()
{
    SudokuGame game;
    float deltaTime = 0.0f;
    while (game.isRunning()) 
    {
        deltaTime = game.getDeltaTime();
        game.update(deltaTime);
        game.render();
    }
    return 0;
}
