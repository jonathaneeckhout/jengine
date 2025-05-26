#include "jengine/visuals/Button.hpp"
#include "jengine/core/Game.hpp"

Button::Button(Vector position, Vector size) : Visual(position), size(size) {}

Button::~Button() {}

void Button::init()
{
    auto position = getPosition();

    body = Game::create<Square>(position, size);

    addChild(body);
}

void Button::setSelectedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    selectedColor = {r, g, b, a};
}

void Button::setPressColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    pressColor = {r, g, b, a};
}