#include "CellInputButton.h"

static const sf::Vector2f CENTERED_OFFSET(20.0f, 10.0f);
static const float CANDIDATE_SPACING = 18.0f;

CellInputButton::CellInputButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& label, const std::function<void()>& onClick, const char& value) :
	Button(position, size, font, label, onClick)
{
	this->value = value;
    auto xOffset = 6.0f + (value - '1') % 3 * CANDIDATE_SPACING;
    auto yOffset = 2.0f + (value - '1') / 3 * CANDIDATE_SPACING;
    _offset = { xOffset, yOffset };
}

void CellInputButton::draw(sf::RenderWindow& window, bool writeMode)
{
    auto textPos = position + (writeMode ? CENTERED_OFFSET : _offset);
    auto textSize = writeMode ? 32 : 15;

    text.setPosition(textPos);
    text.setCharacterSize(textSize);

    Button::draw(window);
}