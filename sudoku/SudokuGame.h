#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "Group.h"
#include "CellViewButton.h"
#include "CellInputButton.h"

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
	void bindCellToView(std::shared_ptr<Cell> cell, int col, int row);
	void createCellGrid();
	void createButtons();
	void createCandidateButtons();
	
	// Runtime

	void pollEvents();
	void mouseButtonPressed(bool leftClick);
	void arrowKeyPressed(sf::Vector2i dir);
	void clickView(CellViewButton& view);
	void textEntered(char input);
	void toggleMode();
	void newGame();
	void resetGame();
	void checkSolution();
	bool hasSolvedPuzzle();
	
	// Variables

	sf::RenderWindow _window;
	sf::Event _event;
	sf::Clock _clock;
	sf::Font _font;
	
	sf::Vector3i _selectedPos; // (col, row, box)
	CellViewButton* _selectedView;
	std::vector<CellViewButton> _cellViews;
	std::vector<CellInputButton> _cellInputs;
	std::vector<Button> _buttons;
	std::vector<Group> _columns;
	std::vector<Group> _rows;
	std::vector<Group> _boxes;
	bool _penOrPencil; // true = pen, false = pencil
	float _runTime;
	float _checkEndTime;
	sf::Text _checkResultText;
};
