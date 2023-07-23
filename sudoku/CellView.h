#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Cell.h"

class CellView 
{
public:
    CellView();
    CellView(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    void draw(sf::RenderWindow& window);
    bool checkClick(const sf::Vector2f& mousePos);
    void changeElementTo(char val);
    void toggleSelect();

private:
    std::shared_ptr<Cell> _cell;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Font _font;
    bool _isSelected = false;
};
