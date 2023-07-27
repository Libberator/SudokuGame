#include "SudokuGame.h"
#include <random>

static const unsigned int VIEW_HEIGHT = 600;
static const unsigned int VIEW_WIDTH = 800;
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
    _font.loadFromFile("resources/ArchitectsDaughter.ttf");

    _selectedView = nullptr;
    _selectedPos = sf::Vector3i(-1, -1, -1);
    _penOrPencil = true;

    createCellGrid();
    createButtons();
    createCandidateButtons();

    _checkResultText.setFont(_font);
    _checkResultText.setCharacterSize(20);
    _checkResultText.setPosition({ 540.0f, 22.0f });
}

void SudokuGame::bindCellToView(std::shared_ptr<Cell> cell, int col, int row)
{
    auto offset = GRID_OFFSET + sf::Vector2f(col / 3 * CELL_SPACING, row / 3 * CELL_SPACING);
    auto pos = offset + sf::Vector2f((CELL_SIZE + CELL_SPACING) * col, (CELL_SIZE + CELL_SPACING) * row);
    sf::Vector2f size(CELL_SIZE, CELL_SIZE);

    CellViewButton view(cell, pos, size, _font);
    _cellViews.push_back(view);
}

inline int const boxIndex(const int col, const int row) { return (col / 3) + (row / 3) * 3; }

void SudokuGame::createCellGrid()
{
    for (int row = 0; row < 9; row++)
    {
        auto& rowGroup = getOrMakeGroup(_rows, row);
        for (int col = 0; col < 9; col++)
        {
            auto& colGroup = getOrMakeGroup(_columns, col);

            auto box = boxIndex(col, row);
            auto& boxGroup = getOrMakeGroup(_boxes, box);

            auto cell = std::make_shared<Cell>(col, row, box);
            rowGroup.cells.push_back(cell);
            colGroup.cells.push_back(cell);
            boxGroup.cells.push_back(cell);

            bindCellToView(cell, col, row);
        }
    }
}

void SudokuGame::createButtons()
{
    Button newGame({ 100.0f, 10.0f }, { 135.0f, 50.0f }, _font, "New Game", [this]() { this->newGame(); });
    _buttons.push_back(newGame);

    Button resetGame({ 245.0f, 10.0f }, { 90.0f, 50.0f }, _font, "Reset", [this]() { this->resetGame(); });
    _buttons.push_back(resetGame);

    Button checkSolution({ 345.0f, 10.0f }, { 180.0f, 50.0f }, _font, "Check Solution", [this]() { this->checkSolution(); });
    _buttons.push_back(checkSolution);

    Button toggleMode({ 605.0f, 150.0f }, { 120.0f, 50.0f }, _font, "Pencil/Ink", [this]() { this->toggleMode(); });
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
        CellInputButton cellInput(position, { 60.0f, 60.0f }, _font, std::to_string(i + 1),
            [this, value]() { this->textEntered(value); }, value);
        _cellInputs.push_back(cellInput);
    }

    Button clearButton = Button({ 635.0f, 405.0f }, { 60.0f, 60.0f }, { 6.0f, 10.0f }, _font, "   0\n(Clear)",
        [this]() { this->textEntered('0'); });
    clearButton.text.setCharacterSize(16);
    _buttons.push_back(clearButton);
}

#pragma endregion

#pragma region Public Methods

void SudokuGame::update(float dt)
{
    _runTime += dt;
    pollEvents();
}

void SudokuGame::render()
{
    _window.clear(sf::Color(50, 50, 50, 255));
    
    // Draw grid cell
    char selectedValue = _selectedView != nullptr ? _selectedView->getValue() : '0';
    for (auto& view : _cellViews)
        view.draw(_window, _selectedPos, selectedValue);

    // Draw cell inputs
    for (auto& cellInput : _cellInputs)
        cellInput.draw(_window, _penOrPencil); // give a bool if we're in Write/Sketch mode
    
    // Draw buttons
    for (auto& button : _buttons)
        button.draw(_window);

    // Draw check result for a short duration after button's clicked
    if (_checkEndTime > _runTime) 
        _window.draw(_checkResultText);

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

void SudokuGame::pollEvents()
{
    while (_window.pollEvent(_event))
    {
        switch (_event.type)
        {
        case sf::Event::MouseButtonPressed:
            if (_event.mouseButton.button == sf::Mouse::Left)
                mouseButtonPressed(true);
            else if (_event.mouseButton.button == sf::Mouse::Right)
                mouseButtonPressed(false);
            break;
        case sf::Event::TextEntered:
            textEntered(_event.text.unicode);
            break;
        case sf::Event::KeyPressed:
            if (_event.key.code == sf::Keyboard::Right) arrowKeyPressed(sf::Vector2i(1, 0));
            else if (_event.key.code == sf::Keyboard::Left) arrowKeyPressed(sf::Vector2i(-1, 0));
            else if (_event.key.code == sf::Keyboard::Up) arrowKeyPressed(sf::Vector2i(0, -1));
            else if (_event.key.code == sf::Keyboard::Down) arrowKeyPressed(sf::Vector2i(0, 1));
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
    for (auto& cellInput : _cellInputs)
    {
        if (cellInput.isClicked(mousePosf))
        {
            cellInput.onClick();
            return;
        }
    }
}

inline int clampAndLoop(int index, int max) { return (index + max) % max; }

void SudokuGame::arrowKeyPressed(sf::Vector2i dir)
{
    if (_selectedView == nullptr) return;
    
    int col = clampAndLoop(_selectedPos.x + dir.x, (int)_columns.size());
    int row = clampAndLoop(_selectedPos.y + dir.y, (int)_rows.size());
    int index = row * 9 + col;
    clickView(_cellViews[index]);
}

void SudokuGame::clickView(CellViewButton& view)
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
    if (_selectedView->isClue()) return;
    if (input >= '0' && input <= '9')
    {
        if (_penOrPencil == true)
            _selectedView->setValue(input, false);
        else if (!_selectedView->hasValue())
            _selectedView->toggleCandidate(input);
    }
}

inline void SudokuGame::toggleMode() { _penOrPencil = !_penOrPencil; }

static int const getRandomNumber(const int& min, const int& maxInclusive) 
{
    std::random_device rng;
    std::mt19937_64 gen(rng());
    std::uniform_int_distribution<int> distribution(min, maxInclusive);
    return distribution(gen);
}

void SudokuGame::newGame()
{
    for (auto& view : _cellViews)
        view.reset(true);

    int rng = getRandomNumber(0, 99);

    std::string puzzle;
    puzzle.resize(81);
    
    sf::FileInputStream stream;
    stream.open("resources/puzzles.csv");
    stream.seek(rng * 165);
    stream.read(const_cast<char*>(puzzle.data()), 81);
    
    for (int i = 0; i < 81; i++)
        _cellViews[i].setValue(puzzle[i], true);
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
        _checkResultText.setFillColor({ 50, 250, 50, 255 });
        _checkResultText.setString("SOLVED!");
    }
    else 
    {
        _checkResultText.setFillColor({ 250, 50, 50, 255 });
        _checkResultText.setString("Not solved");
    }
    
    _checkEndTime = _runTime + 2.0f;
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
