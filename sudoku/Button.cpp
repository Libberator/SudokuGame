#include "Button.h"

Button::Button() { }

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font) :
    _position(position), _size(size), _font(font) { }

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick) :
    Button(position, size, font)
{
    this->_label = label;
    this->onClick = onClick;
}

void Button::draw(sf::RenderWindow& window)
{
    sf::RectangleShape buttonShape(_size);
    auto bgFillColor = sf::Color(230, 230, 230, 255);
    buttonShape.setFillColor(bgFillColor);
    buttonShape.setPosition(_position);
    window.draw(buttonShape);

    sf::Text buttonText(_label, _font, 20);
    auto textFillColor = sf::Color(50, 50, 50, 255);
    buttonText.setFillColor(textFillColor);
    auto textOffset = sf::Vector2f(18.0f, 12.0f);
    buttonText.setPosition(_position + textOffset);
    window.draw(buttonText);
}

bool Button::isClicked(const sf::Vector2f& mousePos)
{
    return mousePos.x >= _position.x && mousePos.x < _position.x + _size.x &&
        mousePos.y >= _position.y && mousePos.y < _position.y + _size.y;
}
