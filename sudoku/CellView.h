#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.h"
#include "Cell.h"

class CellView : public Button
{
public:
    CellView();
    CellView(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    void reset(bool hardReset);
    void draw(sf::RenderWindow& window, sf::Vector3i selected, char selectedValue);
    bool isClue();
    bool hasValue();
    char getValue();
    void setValue(char val, bool isClue);
    void toggleCandidate(char input);

    sf::Vector3i gridPos; // (col, row, box)
    
private:
    std::shared_ptr<Cell> _cell;
};
