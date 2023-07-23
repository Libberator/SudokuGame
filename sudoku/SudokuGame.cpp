#include "SudokuGame.h"

static const float VIEW_HEIGHT = 600.0f;
static const float VIEW_WIDTH = 800.0f;
static const float CELL_SIZE = 50.0f;
static const float CELL_SPACING = 3.0f;
static const sf::Vector2f CELL_OFFSET(175.0f, 50.0f);

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
    _window.clear(sf::Color(50, 50, 50, 255));
    
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
    sf::VideoMode videoMode(VIEW_WIDTH, VIEW_HEIGHT);
    int style = sf::Style::Titlebar | sf::Style::Close; // don't allow re-sizing for now
    _window.create(videoMode, "Sudoku Solver", style);
    
    _window.setVerticalSyncEnabled(true);
}

void SudokuGame::initVariables()
{
    _font.loadFromFile("resources/ArchitectsDaughter.ttf");

    _selectedView = nullptr;

    for (int row = 0; row < 9; row++)
    {
        auto rowGroup = getOrMakeGroup(_rows, row);
        for (int col = 0; col < 9; col++)
        {
            auto colGroup = getOrMakeGroup(_columns, col);

            auto boxIndex = (row / 3) * 3 + (col / 3);
            auto boxGroup = getOrMakeGroup(_boxes, boxIndex);

            auto cell = std::make_shared<Cell>();
            rowGroup->add(cell);
            colGroup->add(cell);
            boxGroup->add(cell);
            
            bindCellToView(cell, row, col);
        }
    }

    // Constraint/Rule
    // For the Cell Candidates, use std::set, and std::set_intersection

    // Visuals:
    // define CELL_SIZE (pixels), CELL_SPACING (pixels) & extra spacing between boxes
    // Bind a CellVisual to a Cell

    // TODO: Keep track of Selected Cell
    
    // On mouse click, either Select New or Deselect (if mouse click is on same object or on none)
    // On keypress, if we have one selected, toggle the digit from Candidates
    // Maybe have a display area of all the possible digits which you can select
    // Right-click to toggle candidates & left-click to select one?
}

std::shared_ptr<Group> SudokuGame::getOrMakeGroup(std::vector<std::shared_ptr<Group>>& groups, int index)
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
    auto offset = CELL_OFFSET + sf::Vector2f(row / 3 * CELL_SPACING, col / 3 * CELL_SPACING);
    auto pos = offset + sf::Vector2f((CELL_SIZE + CELL_SPACING) * row, (CELL_SIZE + CELL_SPACING) * col);
    sf::Vector2f size(CELL_SIZE, CELL_SIZE);

    CellView view(cell, pos, size, _font);
    _cellViews.push_back(view);
}

void SudokuGame::pollEvents()
{
    while (_window.pollEvent(_event))
    {
        switch (_event.type)
        {
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosf((float)mousePos.x, (float)mousePos.y);

                for (auto& view : _cellViews) 
                {
                    if (view.checkClick(mousePosf)) 
                    {
                        clickedView(view);

                        //printf("Selected %i, %i\n", mousePos.x, mousePos.y);

                        break;
                    }
                }
            }
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::TextEntered:
            textEntered(_event.text.unicode);
            /*if (_event.text.unicode < 128)
                printf("%c", _event.text.unicode);*/
            break;
        case sf::Event::Closed:
            _window.close();
            break;
        default:
            break;
        }
    }
}

void SudokuGame::clickedView(CellView& view)
{
    if (_selectedView == &view) 
    {
        _selectedView = nullptr;
    }
    else 
    {
        if (_selectedView != nullptr) _selectedView->toggleSelect();
        _selectedView = &view;
    }
    view.toggleSelect();
}

void SudokuGame::textEntered(int input)
{
    if (_selectedView == nullptr) return;
    if (input >= '0' && input <= '9')
        _selectedView->changeElementTo(input);
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
