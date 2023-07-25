#include "SudokuGame.h"

static const float VIEW_HEIGHT = 600.0f;
static const float VIEW_WIDTH = 800.0f;
static const float CELL_SIZE = 50.0f;
static const float CELL_SPACING = 2.0f;
static const sf::Vector2f GRID_OFFSET(70.0f, 70.0f);

#pragma region Initializing

SudokuGame::SudokuGame()
{
    initWindow();
    initVariables();
}

void SudokuGame::initWindow()
{
    sf::VideoMode videoMode(VIEW_WIDTH, VIEW_HEIGHT);
    int style = sf::Style::Titlebar | sf::Style::Close; // don't allow re-sizing for now
    _window.create(videoMode, "Sudoku Solver", style);

    _window.setVerticalSyncEnabled(true);
}

inline int boxIndex(int row, int col) { return (row / 3) * 3 + (col / 3); }

void SudokuGame::initVariables()
{
    _font.loadFromFile("resources/ArchitectsDaughter.ttf");

    _selectedView = nullptr;
    _selectedPos = sf::Vector3i(-1, -1, -1);

    for (int row = 0; row < 9; row++)
    {
        auto& rowGroup = getOrMakeGroup(_rows, row);
        for (int col = 0; col < 9; col++)
        {
            auto& colGroup = getOrMakeGroup(_columns, col);

            auto box = boxIndex(row, col);
            auto& boxGroup = getOrMakeGroup(_boxes, box);

            auto cell = std::make_shared<Cell>(row, col, box);
            rowGroup.cells.push_back(cell);
            colGroup.cells.push_back(cell);
            boxGroup.cells.push_back(cell);

            bindCellToView(cell, row, col);
        }
    }
}

Group& SudokuGame::getOrMakeGroup(std::vector<Group>& groups, int index)
{
    if (groups.size() > index)
        return groups[index];
    groups.emplace_back();
    return groups.back();
}

void SudokuGame::bindCellToView(std::shared_ptr<Cell> cell, int row, int col)
{
    auto offset = GRID_OFFSET + sf::Vector2f(row / 3 * CELL_SPACING, col / 3 * CELL_SPACING);
    auto pos = offset + sf::Vector2f((CELL_SIZE + CELL_SPACING) * row, (CELL_SIZE + CELL_SPACING) * col);
    sf::Vector2f size(CELL_SIZE, CELL_SIZE);

    CellView view(cell, pos, size, _font);
    _cellViews.push_back(view);
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
    char selectedValue = _selectedView != nullptr ? _selectedView->getValue() : '0';
    for (auto& view : _cellViews)
        view.draw(_window, _selectedPos, selectedValue);

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

// 3 buttons:
// -New Game (difficulty options?). Two methods: Restart (Reset), Fill with puzzle (check clipboard/file?)
// -Check Solution (bool toggle?)
// -Solve Puzzle

// Need a way to draw visual candidates, and toggle between writing modes
// Tab/Space to toggle? 
// Arrow keys to move selection (wrap around). Store Vector2i for Grid Pos
// detect backspace or delete to clear cell? Undo button?
// On keypress, if we have one selected, toggle the digit from Candidates
// Maybe have a display area of all the possible digits which you can select

// Constraint/Rule
// For the Cell Candidates, use std::set, and std::set_intersection

void SudokuGame::pollEvents()
{
    while (_window.pollEvent(_event))
    {
        switch (_event.type)
        {
        case sf::Event::MouseButtonPressed:
            // NOTE: this will pass if you're holding in left-button, but click right-button :/
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                mouseButtonPressed(true);
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
                mouseButtonPressed(false);
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::TextEntered:
            textEntered(_event.text.unicode);
            break;
        case sf::Event::Closed:
            _window.close();
            break;
        default:
            break;
        }
    }
}

void SudokuGame::mouseButtonPressed(bool leftClick)
{
    auto pixelPos = sf::Mouse::getPosition(_window);
    sf::Vector2f mousePosf((float)pixelPos.x, (float)pixelPos.y);

    for (auto& view : _cellViews)
    {
        if (view.isClicked(mousePosf))
        {
            clickView(view);
            return;
        }
    }

    // TODO: add checks for other Buttons

    // TODO: add checks for numbers being pressed IF we have something selected
}

void SudokuGame::clickView(CellView& view)
{
    if (_selectedView == &view)
    {
        _selectedView = nullptr;
        _selectedPos = sf::Vector3i(-1, -1, -1);
    }
    else
    {
        _selectedView = &view;
        _selectedPos = view.gridPos;
    }
}

void SudokuGame::textEntered(int input)
{
    if (_selectedView == nullptr) return;
    if (_selectedView->cell->isClue) return;
    if (input >= '0' && input <= '9')
        _selectedView->setValue(input);
}

bool SudokuGame::hasSolvedPuzzle()
{
    for (auto& group : _rows) 
        if (!group.isSolved()) return false;

    for (auto& group : _columns)
        if (!group.isSolved()) return false;

    for (auto& group : _boxes)
        if (!group.isSolved()) return false;

    return true;
}

#pragma endregion
