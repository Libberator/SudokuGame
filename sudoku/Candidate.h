#pragma once
#include "Button.h"

class Candidate : public Button
{
public:
	Candidate(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick, const char& value);

	void draw(sf::RenderWindow& window, bool writeMode);

	char value;

private:
	sf::Vector2f _offset;
};

