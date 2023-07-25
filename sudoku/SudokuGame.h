#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "Group.h"
#include "CellView.h"
#include "Candidate.h"

class SudokuGame
{
public:
	SudokuGame();
	virtual ~SudokuGame() {}

	void update(float dt);
	void render();
	const bool isRunning() const;
	const float getDeltaTime();

private:
	// Initialization
	
	void initWindow();
	void initVariables();
	void bindCellToView(std::shared_ptr<Cell> cell, int row, int col);
	void createCellGrid();
	void createButtons();
	void createCandidateButtons();
	
	// Runtime

	void pollEvents();
	void mouseButtonPressed(bool leftClick);
	void clickView(CellView& view);
	void textEntered(char input);
	void toggleMode();
	void newGame();
	void resetGame();
	void checkSolution();
	bool hasSolvedPuzzle();
	
	sf::RenderWindow _window;
	sf::Event _event;
	sf::Clock _clock;
	sf::Font _font;
	
	sf::Vector3i _selectedPos; // (row, col, box)
	CellView* _selectedView;
	std::vector<CellView> _cellViews;
	std::vector<Button> _buttons;
	std::vector<Candidate> _candidates;
	std::vector<Group> _rows;
	std::vector<Group> _columns;
	std::vector<Group> _boxes;
	bool _writeMode;
};
