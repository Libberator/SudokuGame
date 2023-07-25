#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
	Button();
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick);

	virtual void draw(sf::RenderWindow& window);
	virtual bool isClicked(const sf::Vector2f& mousePos);
	
	std::function<void()> onClick;

protected:
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::Font _font;
	std::string _label;
};
