#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "Cell.h"

class CellView 
{
public:
    CellView(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::function<void()>& onClick);

    void draw(sf::RenderWindow& window);

    bool checkClick(const sf::Vector2f& mousePos);

private:
    std::shared_ptr<Cell> _cell;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Font _font;
    std::function<void()> _onClick;
};
