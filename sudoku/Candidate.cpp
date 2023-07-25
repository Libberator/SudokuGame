#include "Candidate.h"

static const sf::Vector2f CENTERED_OFFSET(20.0f, 10.0f);
static const float CANDIDATE_SPACING = 18.0f;

Candidate::Candidate(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick, const char& value) :
	Button(position, size, font, label, onClick)
{
	this->value = value;
    auto xOffset = 6.0f + (value - '1') % 3 * CANDIDATE_SPACING;
    auto yOffset = 2.0f + (value - '1') / 3 * CANDIDATE_SPACING;
    _offset = { xOffset, yOffset };
}

void Candidate::draw(sf::RenderWindow& window, bool writeMode)
{
    sf::RectangleShape buttonShape(_size);
    auto bgFillColor = sf::Color(230, 230, 230, 255);
    buttonShape.setFillColor(bgFillColor);
    buttonShape.setPosition(_position);
    window.draw(buttonShape);

    sf::Text buttonText(_label, _font, writeMode ? 32 : 15);
    auto textFillColor = sf::Color(50, 50, 50, 255);
    buttonText.setFillColor(textFillColor);
    buttonText.setPosition(_position + (writeMode ? CENTERED_OFFSET : _offset));
    window.draw(buttonText);
}