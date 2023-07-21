#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button 
{
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label, const sf::Font& font, const std::function<void()>& onClick);

    void draw(sf::RenderWindow& window);

    void checkClick(const sf::Vector2f& mousePos);

private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Font font;
    std::string label;
    std::function<void()> onClick;
};
