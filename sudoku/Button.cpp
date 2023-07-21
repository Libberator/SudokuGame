#include "Button.h"

Button::Button(
    const sf::Vector2f& position, 
    const sf::Vector2f& size, 
    const std::string& label,
    const sf::Font& font,
    const std::function<void()>& onClick)
    : position(position), size(size), label(label), onClick(onClick), font(font) {}

void Button::draw(sf::RenderWindow& window)
{
    sf::RectangleShape buttonShape(size);
    buttonShape.setFillColor({255, 255, 255, 255});
    buttonShape.setPosition(position);
    window.draw(buttonShape);

    sf::Text buttonText(label, font, 20);
    buttonText.setFillColor({ 0, 0, 0, 255 });
    buttonText.setPosition(position + sf::Vector2f(10.f, 10.f));
    window.draw(buttonText);
}

void Button::checkClick(const sf::Vector2f& mousePos)
{
    if (mousePos.x >= position.x && mousePos.x < position.x + size.x &&
        mousePos.y >= position.y && mousePos.y < position.y + size.y) {
        onClick();
    }
}
