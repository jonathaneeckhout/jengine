#include "jengine/visuals/Button.hpp"
#include "jengine/core/Game.hpp"

Button::Button(Vector position, Vector size) : Visual(position), size(size) {}

Button::~Button() {}

void Button::init()
{
    body = Game::create<Square>(Vector(), size);

    addChild(body);
}

void Button::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Visual::setColor(r, g, b, a);

    updateColor();
}

void Button::setSelectedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    selectedColor = {r, g, b, a};

    updateColor();
}

void Button::setPressColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    pressColor = {r, g, b, a};

    updateColor();
}

void Button::updateColor()
{
    switch (state)
    {
    case Button::IDLE:
        body->setColor(color.r, color.g, color.b, color.a);
        break;
    case SELECTED:
        body->setColor(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
        break;
    case PRESSED:
        body->setColor(pressColor.r, pressColor.g, pressColor.b, pressColor.a);
        break;
    }
}

void Button::setIdle()
{
    state = Button::IDLE;

    updateColor();
}

void Button::setSelected()
{
    state = Button::SELECTED;

    updateColor();
}

void Button::setPressed()
{
    state = Button::PRESSED;

    updateColor();
}
