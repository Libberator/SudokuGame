#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "Group.h"
#include "CellView.h"

class SudokuGame
{
public:
	// Constructor / Destructor

	SudokuGame();
	virtual ~SudokuGame() {}

	// Public Methods
	
	void update(float dt);
	void render();
	const bool isRunning() const;
	const float getDeltaTime();

private:
	// Private Variables
	
	sf::RenderWindow _window;
	sf::Event _event;
	sf::Clock _clock;
	sf::Font _font;
	
	CellView* _selectedView;
	sf::Vector3i _selectedPos; // (row, col, box)
	std::vector<CellView> _cellViews;
	std::vector<Group> _rows;
	std::vector<Group> _columns;
	std::vector<Group> _boxes;

	// Private Methods
	
	void initWindow();
	void initVariables();
	Group& getOrMakeGroup(std::vector<Group>& groups, int index);
	void bindCellToView(std::shared_ptr<Cell> cell, int row, int col);
	void pollEvents();
	void mouseButtonPressed(bool leftClick);
	void clickView(CellView& view);
	void textEntered(int input);
	bool hasSolvedPuzzle();
};
