#include "CellViewButton.h"

static const sf::Color BG_DEFAULT(230, 230, 230, 255); // default background fill
static const sf::Color BG_SELECTED(120, 190, 200, 255);
static const sf::Color BG_SELECTED_SIMILAR(150, 240, 250, 255); // same digit
static const sf::Color BG_HIGHLIGHTED(200, 250, 250, 255); // cols, rows, boxes

static const sf::Color TEXT_CLUE_COLOR(0, 0, 0, 255);
static const sf::Vector2f TEXT_OFFSET(16.0f, 6.0f);
static const unsigned int TEXT_VALUE_SIZE = 30;
static const unsigned int TEXT_CANDIDATE_SIZE = 11;

CellViewButton::CellViewButton() : Button() { }

CellViewButton::CellViewButton(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    : Button(position, size, font), _cell(cell)
{
    gridPos = sf::Vector3i(cell->col, cell->row, cell->box);
    text.setCharacterSize(TEXT_VALUE_SIZE);
    text.setStyle(sf::Text::Bold);
    text.setPosition(position + TEXT_OFFSET);
}

void CellViewButton::reset(bool hardReset) { _cell->reset(hardReset); }

void CellViewButton::draw(sf::RenderWindow& window, sf::Vector3i selected, char selectedValue)
{
    auto fillColor = gridPos == selected ? BG_SELECTED :
        selectedValue != '0' && selectedValue == getValue() ? BG_SELECTED_SIMILAR :
        selected.x == gridPos.x || selected.y == gridPos.y || selected.z == gridPos.z ? BG_HIGHLIGHTED :
        BG_DEFAULT;
    rect.setFillColor(fillColor);
    window.draw(rect);

    if (getValue() != '0')
    {
        auto color = isClue() ? TEXT_CLUE_COLOR : textColor;
        text.setFillColor(color);
        text.setString(getValue());
        window.draw(text);
    }
    else
    {
        // draw any candidates
        for (char c : _cell->candidates) 
        {
            auto xOffset = 4.0f + (c - '1') % 3 * 16.0f;
            auto yOffset = 2.0f + (c - '1') / 3 * 16.0f;
            sf::Vector2f offset(xOffset, yOffset);
            
            sf::Text candidate(c, font, TEXT_CANDIDATE_SIZE);
            candidate.setFillColor(textColor);
            candidate.setPosition(position + offset);
            window.draw(candidate);
        }
    }
}

bool CellViewButton::isClue() { return _cell->isClue; }

bool CellViewButton::hasValue() { return _cell->hasValue(); }

char CellViewButton::getValue() { return _cell->value; }

void CellViewButton::setValue(char val, bool isClue) { _cell->setValue(val, isClue); }

void CellViewButton::toggleCandidate(char input)
{
    if (input == '0') 
    {
        _cell->candidates.clear();
        return;
    }

    if (_cell->candidates.count(input) == 1)
        _cell->candidates.erase(input);
    else
        _cell->candidates.insert(input);
}
