#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf; // I know this might be frowned upon, but I'm doing it anyways

class SudokuGame
{
public:
	// Constructor / Destructor

	SudokuGame();
	virtual ~SudokuGame();

	// Public Methods
	
	void update(float dt);
	void render();
	const bool isRunning() const;
	const float getDeltaTime();

private:
	// Private Variables
	
	RenderWindow window;
	Event ev;
	Clock clock;

	// Private Methods
	
	void initWindow();
	void initVariables();
	void pollEvents();
};
