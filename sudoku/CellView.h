#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Button.h"
#include "Cell.h"

class CellView : public Button
{
public:
    CellView();
    CellView(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    void draw(sf::RenderWindow& window, sf::Vector3i selected, char selectedValue) override;
    void setValue(char val);
    char getValue();
    
    sf::Vector3i gridPos; // (row, col, box)
    std::shared_ptr<Cell> cell;
};
