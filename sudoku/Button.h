#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

struct Button
{
	Button();
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& textOffset, const sf::Font& font);
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick);
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& textOffset, const sf::Font& font, const std::string& label, const std::function<void()>& onClick);

	virtual void draw(sf::RenderWindow& window);
	virtual bool isClicked(const sf::Vector2f& mousePos);
	
	std::function<void()> onClick;
	
	sf::RectangleShape rect;
	sf::Vector2f position;
	sf::Vector2f rectSize;
	sf::Color rectColor = { 230, 230, 230, 255 };
	
	sf::Text text;
	sf::Vector2f textOffset = { 18.0f, 12.0f };
	sf::Color textColor = { 50, 50, 50, 255 };
	unsigned int textSize = 20;
	sf::Font font;
	std::string label;
};