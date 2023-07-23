#include "CellView.h"

static const sf::Vector2f TEXT_OFFSET(18.0f, 12.0f);

CellView::CellView() { }

CellView::CellView(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    : _cell(cell), _position(position), _size(size), _font(font) {}

void CellView::draw(sf::RenderWindow& window)
{
    sf::RectangleShape buttonShape(_size);
    auto fillColor = _isSelected ? sf::Color(230, 230, 150, 255) : sf::Color(230, 230, 230, 255);
    buttonShape.setFillColor(fillColor);
    buttonShape.setPosition(_position);
    window.draw(buttonShape);

    sf::Text buttonText(_cell->element, _font, 20);
    buttonText.setFillColor(sf::Color(50, 50, 50, 255));
    buttonText.setPosition(_position + TEXT_OFFSET);
    window.draw(buttonText);
}

bool CellView::checkClick(const sf::Vector2f& mousePos)
{
    if (mousePos.x >= _position.x && mousePos.x < _position.x + _size.x &&
        mousePos.y >= _position.y && mousePos.y < _position.y + _size.y)
    {
        return true;
    }
    return false;
}

void CellView::changeElementTo(char val)
{
    if (_cell->isClue) return;
    _cell->element = val;
}

void CellView::toggleSelect()
{
    _isSelected = !_isSelected;
}
