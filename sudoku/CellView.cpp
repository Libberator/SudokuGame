#include "CellView.h"

CellView::CellView(
    std::shared_ptr<Cell> cell,
    const sf::Vector2f& position, 
    const sf::Vector2f& size, 
    const sf::Font& font,
    const std::function<void()>& onClick)
    : _cell(cell), _position(position), _size(size), _font(font), _onClick(onClick) {}

void CellView::draw(sf::RenderWindow& window)
{
    sf::RectangleShape buttonShape(_size);
    buttonShape.setFillColor(sf::Color(230, 230, 230, 255));
    buttonShape.setPosition(_position);
    window.draw(buttonShape);

    sf::Text buttonText(_cell->element, _font, 20);
    buttonText.setFillColor(sf::Color(50, 50, 50, 255));
    buttonText.setPosition(_position + sf::Vector2f(10.f, 10.f));
    window.draw(buttonText);
}

bool CellView::checkClick(const sf::Vector2f& mousePos)
{
    if (mousePos.x >= _position.x && mousePos.x < _position.x + _size.x &&
        mousePos.y >= _position.y && mousePos.y < _position.y + _size.y)
    {
        _onClick();
        return true;
    }
    return false;
}
