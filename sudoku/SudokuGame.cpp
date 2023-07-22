#include "SudokuGame.h"

static const float VIEW_HEIGHT = 600.0f;
static const float VIEW_WIDTH = 800.0f;

#pragma region Constructor / Destructor

SudokuGame::SudokuGame()
{
    initWindow();
    initVariables();
}

#pragma endregion

#pragma region Public Methods

void SudokuGame::update(float dt)
{
    pollEvents();
}

void SudokuGame::render()
{
    _window.clear(Color(50, 50, 50, 255));
    
    // Draw game object
    for (auto& view : _cellViews)
    {
        view.draw(_window);
    }

    _window.display();
}

const bool SudokuGame::isRunning() const
{
    return _window.isOpen();
}

const float SudokuGame::getDeltaTime()
{
    return _clock.restart().asSeconds();
}

#pragma endregion

#pragma region Private Methods

void SudokuGame::initWindow()
{
    VideoMode videoMode(VIEW_WIDTH, VIEW_HEIGHT);
    int style = Style::Titlebar | Style::Close; // don't allow re-sizing for now
    _window.create(videoMode, "Sudoku Solver", style);
    
    _window.setVerticalSyncEnabled(true);
}

void SudokuGame::initVariables()
{
    _font.loadFromFile("resources/ArchitectsDaughter.ttf");

    // TODO: set up sudoku data and bind some UI to it
    _cellViews.clear();
    for (int row = 0; row < 9; row++)
    {
        auto rowGroup = getOrMakeGroup(_rows, row);
        for (int col = 0; col < 9; col++)
        {
            auto colGroup = getOrMakeGroup(_columns, col);

            auto boxIndex = (row / 3) * 3 + (col / 3);
            auto boxGroup = getOrMakeGroup(_boxes, boxIndex);

            std::shared_ptr<Cell> cell = std::make_shared<Cell>();
            rowGroup->add(cell);
            colGroup->add(cell);
            boxGroup->add(cell);
            
            bindCellToView(cell, row, col);
        }
    }

    // Cells (81). Element (aka digit, but can be letter too), Candidates - Solved. isClue/isGiven/locked
    // Groups (rows, columns, boxes)
    // Grid
    // Constraint/Rule
    // For the Cell Candidates, use std::set, and std::set_intersection

    // Visuals:
    // define CELL_SIZE (pixels), CELL_SPACING (pixels) & extra spacing between boxes
    // Bind a CellVisual to a Cell

    // Keep track of Selected Cell
    // On mouse click, either Select New or Deselect (if mouse click is on same object or on none)
    // On keypress, if we have one selected, toggle the digit from Candidates
    // Maybe have a display area of all the possible digits which you can select
    // Right-click to toggle candidates & left-click to select one?

    /*Button button({ 100.f, 100.f }, { 250.f, 60.f }, "Click Me", _font,
        []() { printf("Button Clicked!\n"); }
    );
    _buttons.push_back(button);*/
}

std::shared_ptr<Group> SudokuGame::getOrMakeGroup(std::vector<std::shared_ptr<Group>> groups, int index) 
{
    std::shared_ptr<Group> result;
    if (groups.size() > index)
        result = groups[index];
    else
    {
        result = std::make_shared<Group>();
        groups.push_back(result);
    }
    return result;
}

void SudokuGame::bindCellToView(std::shared_ptr<Cell> cell, int row, int col)
{
    Vector2f pos(100.0f * row, 100.0f * col);
    Vector2f size(50.0f, 50.0f);

    CellView view(cell, pos, size, _font, []() { printf("Button Clicked!\n"); });
    _cellViews.push_back(view);
}

void SudokuGame::pollEvents()
{
    while (_window.pollEvent(_event))
    {
        switch (_event.type)
        {
        case Event::MouseButtonPressed:
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Vector2i mousePos = Mouse::getPosition(_window);
                Vector2f mousePosf((float)mousePos.x, (float)mousePos.y);

                for (auto& view : _cellViews) 
                    if (view.checkClick(mousePosf)) break;
                
                //printf("Mouse Pressed at %i, %i\n", mousePos.x, mousePos.y);
                //square.setPosition((float)mousePos.x, (float)mousePos.y);
            }
            break;
        case Event::MouseButtonReleased:
            break;
        case Event::MouseMoved:
            break;
        case Event::TextEntered:
            if (_event.text.unicode < 128)
                printf("%c", _event.text.unicode);
            break;
        case Event::Closed:
            _window.close();
            break;
        default:
            break;
        }
    }
}

bool SudokuGame::hasSolvedPuzzle()
{
    for (auto& group : _rows) 
        if (!group->isSolved()) return false;

    for (auto& group : _columns)
        if (!group->isSolved()) return false;

    for (auto& group : _boxes)
        if (!group->isSolved()) return false;

    return true;
}

#pragma endregion
