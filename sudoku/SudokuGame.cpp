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
    newGame();
}

void SudokuGame::initWindow()
{
    sf::VideoMode videoMode(VIEW_WIDTH, VIEW_HEIGHT);
    int style = sf::Style::Titlebar | sf::Style::Close; // don't allow re-sizing for now
    _window.create(videoMode, "Sudoku Solver", style);

    _window.setVerticalSyncEnabled(true);
}

inline Group& getOrMakeGroup(std::vector<Group>& groups, int index)
{
    if (groups.size() > index)
        return groups[index];
    groups.emplace_back();
    return groups.back();
}

void SudokuGame::initVariables()
{
    //_font.loadFromFile("resources/Gravity-Book.ttf");
    _font.loadFromFile("resources/ArchitectsDaughter.ttf");

    _selectedView = nullptr;
    _selectedPos = sf::Vector3i(-1, -1, -1);
    _writeMode = true;

    createCellGrid();
    createButtons();
    createCandidateButtons();
}

void SudokuGame::bindCellToView(std::shared_ptr<Cell> cell, int row, int col)
{
    auto offset = GRID_OFFSET + sf::Vector2f(row / 3 * CELL_SPACING, col / 3 * CELL_SPACING);
    auto pos = offset + sf::Vector2f((CELL_SIZE + CELL_SPACING) * row, (CELL_SIZE + CELL_SPACING) * col);
    sf::Vector2f size(CELL_SIZE, CELL_SIZE);

    CellView view(cell, pos, size, _font);
    _cellViews.push_back(view);
}

inline int const boxIndex(const int row, const int col) { return (row / 3) * 3 + (col / 3); }

void SudokuGame::createCellGrid()
{
    
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

void SudokuGame::createButtons()
{
    Button newGame({ 90.0f, 10.0f }, { 140.0f, 50.0f }, _font, "New Game", [this]() { this->newGame(); });
    _buttons.push_back(newGame);

    Button resetGame({ 240.0f, 10.0f }, { 90.0f, 50.0f }, _font, "Reset", [this]() { this->resetGame(); });
    _buttons.push_back(resetGame);

    Button checkSolution({ 340.0f, 10.0f }, { 180.0f, 50.0f }, _font, "Check Solution", [this]() { this->checkSolution(); });
    _buttons.push_back(checkSolution);

    Button toggleMode({ 590.0f, 140.0f }, { 155.0f, 50.0f }, _font, "Toggle Mode", [this]() { this->toggleMode(); });
    _buttons.push_back(toggleMode);
}

void SudokuGame::createCandidateButtons()
{
    for (int i = 0; i < 9; i++)
    {
        auto value = '1' + i;
        auto xOffset = 65.0f * (i % 3);
        auto yOffset = 65.0f * (i / 3);
        sf::Vector2f position(570.0f + xOffset, 210.0f + yOffset);
        Candidate candidate = Candidate(position, { 60.0f, 60.0f }, _font, std::to_string(i + 1),
            [this, value]() { this->textEntered(value); }, value);
        _candidates.push_back(candidate);
    }

    // TODO: Add customization for each Button - _defaultTextOffset, _defaultTextSize, etc.
    Button clearButton = Button({ 635.0f, 405.0f }, { 60.0f, 60.0f }, _font, "  0\n(Clear)",
        [this]() { this->textEntered('0'); });
    _buttons.push_back(clearButton);
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
    
    // Draw grid cell
    char selectedValue = _selectedView != nullptr ? _selectedView->getValue() : '0';
    for (auto& view : _cellViews)
        view.draw(_window, _selectedPos, selectedValue);

    // Draw buttons
    for (auto& button : _buttons)
        button.draw(_window);

    // Draw candidates
    for (auto& candidate : _candidates)
        candidate.draw(_window, _writeMode); // give a bool if we're in Write/Sketch mode

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

// TODO's:
// -New Game (difficulty options?). Fill with puzzle (check clipboard/file?)
// -Solve Puzzle
// Arrow keys to move selection (wrap around)
// detect backspace or delete to clear cell? 
// Undo button? would require implementing CommandPattern
// Constraint/Rule <algorithms>
// For the Cell Candidates, use std::set_intersection to narrow things down

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
    if (!leftClick)
    {
        toggleMode();
        return;
    }

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

    for (auto& button : _buttons) 
    {
        if (button.isClicked(mousePosf)) 
        {
            button.onClick();
            return;
        }
    }

    if (_selectedView == nullptr) return;
    for (auto& candidate : _candidates)
    {
        if (candidate.isClicked(mousePosf))
        {
            candidate.onClick();
            return;
        }
    }
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

void SudokuGame::textEntered(char input)
{
    if (_selectedView == nullptr) return;
    if (input >= '0' && input <= '9')
    {
        if (_writeMode == true)
            _selectedView->setValue(input, false);
        else if (!_selectedView->hasValue())
            _selectedView->toggleCandidate(input);
    }
}

void SudokuGame::toggleMode()
{
    _writeMode = !_writeMode;
    printf("Toggle mode\n");
}

void SudokuGame::newGame()
{
    for (auto& view : _cellViews)
        view.reset(true);

    printf("New Game\n");
}

void SudokuGame::resetGame()
{
    for (auto& view : _cellViews)
        view.reset(false);
}

void SudokuGame::checkSolution()
{
    if (hasSolvedPuzzle()) 
    {
        printf("Solved!\n"); // TODO: victory screen
    }
    else
    {
        printf("Not solved yet\n"); // TODO: display message
    }
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
