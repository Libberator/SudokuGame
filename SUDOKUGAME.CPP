#include "SudokuGame.h"

static const float VIEW_HEIGHT = 600.0f;
static const float VIEW_WIDTH = 800.0f;

#pragma region Constructor / Destructor

SudokuGame::SudokuGame()
{
    initWindow();
    initVariables();
}

SudokuGame::~SudokuGame()
{
}

#pragma endregion

#pragma region Public Methods

void SudokuGame::update(float dt)
{
    pollEvents();
}

void SudokuGame::render()
{
    window.clear(Color(180, 180, 180, 255));
    
    // Draw game object
    //window->draw(square);
    window.display();
}

const bool SudokuGame::isRunning() const
{
    return window.isOpen();
}

const float SudokuGame::getDeltaTime()
{
    return clock.restart().asSeconds();
}

#pragma endregion

#pragma region Private Methods

void SudokuGame::initWindow()
{
    VideoMode videoMode(VIEW_WIDTH, VIEW_HEIGHT);
    int style = Style::Titlebar | Style::Close; // don't allow re-sizing for now
    window.create(videoMode, "Sudoku Solver", style);
    
    window.setVerticalSyncEnabled(true);
}

void SudokuGame::initVariables()
{

}

void SudokuGame::pollEvents()
{
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case Event::MouseButtonPressed:
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Vector2i mousePos = Mouse::getPosition(window);
                printf("Mouse Pressed at %i, %i\n", mousePos.x, mousePos.y);
                //square.setPosition((float)mousePos.x, (float)mousePos.y);
            }
            break;
        case Event::MouseButtonReleased:
            break;
        case Event::MouseMoved:
            break;
        case Event::TextEntered:
            if (ev.text.unicode < 128)
                printf("%c", ev.text.unicode);
            break;
        case Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

#pragma endregion
