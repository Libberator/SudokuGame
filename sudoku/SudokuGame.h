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
	std::vector<CellView> _cellViews;
	std::vector<std::shared_ptr<Group>> _rows;
	std::vector<std::shared_ptr<Group>> _columns;
	std::vector<std::shared_ptr<Group>> _boxes;

	// Private Methods
	
	void initWindow();
	void initVariables();
	std::shared_ptr<Group> getOrMakeGroup(std::vector<std::shared_ptr<Group>>& groups, int index);
	void bindCellToView(std::shared_ptr<Cell> cell, int row, int col);
	void pollEvents();
	void clickedView(CellView& view);
	void textEntered(int input);
	bool hasSolvedPuzzle();
};
