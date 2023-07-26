#include "Button.h"

Button::Button() { }

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font) :
    position(position), rectSize(size), font(font)
{
    rect.setPosition(position);
    rect.setSize(size);
    text.setFont(font);
    
    rect.setFillColor(rectColor);
    text.setPosition(position + textOffset);
    text.setCharacterSize(textSize);
    text.setFillColor(textColor);
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& textOffset, const sf::Font& font) :
    Button(position, size, font)
{
    this->textOffset = textOffset;
    text.setPosition(position + textOffset);
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick) :
    Button(position, size, font)
{
    this->label = label;
    this->onClick = onClick;
    text.setString(label);
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& textOffset, const sf::Font& font, const std::string& label, const std::function<void()>& onClick) :
    Button(position, size, textOffset, font)
{
    this->label = label;
    this->onClick = onClick;
    text.setString(label);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(rect);
    window.draw(text);
}

bool Button::isClicked(const sf::Vector2f& mousePos)
{
    return mousePos.x >= position.x && mousePos.x < position.x + rectSize.x &&
        mousePos.y >= position.y && mousePos.y < position.y + rectSize.y;
}
