#include "CellView.h"

static const sf::Color BG_DEFAULT(230, 230, 230, 255); // default background fill
static const sf::Color BG_SELECTED(120, 190, 200, 255);
static const sf::Color BG_SELECTED_SIMILAR(150, 240, 250, 255); // same digit
static const sf::Color BG_HIGHLIGHTED(200, 250, 250, 255); // rows, cols, boxes

static const sf::Color TEXT_CLUE(0, 0, 0, 255); // should let user know it's not editable
static const sf::Color TEXT_VALUE(50, 50, 50, 255); // user-entered value
static const sf::Vector2f TEXT_OFFSET(16.0f, 6.0f);
static const unsigned int TEXT_VALUE_SIZE = 30;
static const unsigned int TEXT_CANDIDATE_SIZE = 11;

CellView::CellView() : Button() { }

CellView::CellView(std::shared_ptr<Cell> cell, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    : Button(position, size, font), _cell(cell)
{
    gridPos = sf::Vector3i(cell->row, cell->col, cell->box);
}

void CellView::reset(bool hardReset)
{
    _cell->reset(hardReset);
}

void CellView::draw(sf::RenderWindow& window, sf::Vector3i selected, char selectedValue)
{
    sf::RectangleShape buttonShape(_size);
    auto fillColor = gridPos == selected ? BG_SELECTED :
        selectedValue != '0' && selectedValue == getValue() ? BG_SELECTED_SIMILAR :
        selected.x == gridPos.x || selected.y == gridPos.y || selected.z == gridPos.z ? BG_HIGHLIGHTED :
        BG_DEFAULT;
    buttonShape.setFillColor(fillColor);
    buttonShape.setPosition(_position);
    window.draw(buttonShape);

    if (getValue() != '0')
    {
        sf::Text buttonText(getValue(), _font, TEXT_VALUE_SIZE);
        buttonText.setStyle(sf::Text::Bold);
        buttonText.setFillColor(isClue() ? TEXT_CLUE : TEXT_VALUE);
        buttonText.setPosition(_position + TEXT_OFFSET);
        window.draw(buttonText);
    }
    else
    {
        // draw any candidates
        for (char c : _cell->candidates) 
        {
            auto xOffset = 4.0f + (c - '1') % 3 * 16.0f;
            auto yOffset = 2.0f + (c - '1') / 3 * 16.0f;
            sf::Vector2f offset(xOffset, yOffset);
            sf::Text candidate(c, _font, TEXT_CANDIDATE_SIZE);
            candidate.setFillColor(TEXT_VALUE);
            candidate.setPosition(_position + offset);
            window.draw(candidate);
        }
    }
}

bool CellView::hasValue()
{
    return _cell->hasValue();
}

void CellView::setValue(char val, bool isClue)
{
    _cell->setValue(val, isClue);
}

char CellView::getValue()
{
    return _cell->value;
}

void CellView::toggleCandidate(char candidate)
{
    if (candidate == '0') 
    {
        _cell->candidates.clear();
        return;
    }

    if (_cell->candidates.count(candidate) == 1)
        _cell->candidates.erase(candidate);
    else
        _cell->candidates.insert(candidate);
}

bool CellView::isClue()
{
    return _cell->isClue;
}
