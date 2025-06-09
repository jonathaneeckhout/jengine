#include "jengine/components/ButtonComponent.hpp"

ButtonComponent::ButtonComponent(Vector position, Vector size) : size(size)
{
    setName("ButtonComponent");

    TransformComponent *transform = new TransformComponent(position);
    addChild(transform);

    button = new SquareComponent(position, size);
    addChild(button);

    events.createEvent<>("onPressed");
    events.createEvent<>("onReleased");

    updateColor();
}

void ButtonComponent::setIdle()
{
    if (state == ButtonComponent::PRESSED)
    {
        events.trigger("onReleased");
    }

    state = ButtonComponent::IDLE;

    updateColor();
}

void ButtonComponent::setSelected()
{
    if (state == ButtonComponent::PRESSED)
    {
        events.trigger("onReleased");
    }

    state = ButtonComponent::SELECTED;

    updateColor();
}

void ButtonComponent::setPressed()
{
    if (state != ButtonComponent::PRESSED)
    {
        events.trigger("onPressed");
    }

    state = ButtonComponent::PRESSED;

    updateColor();
}

void ButtonComponent::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    color = {r, g, b, a};

    updateColor();
}

void ButtonComponent::setSelectedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    selectedColor = {r, g, b, a};

    updateColor();
}

void ButtonComponent::setPressedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    pressedColor = {r, g, b, a};

    updateColor();
}

void ButtonComponent::updateColor()
{
    switch (state)
    {
    case ButtonComponent::IDLE:
        button->setColor(color.r, color.g, color.b, color.a);
        break;
    case ButtonComponent::SELECTED:
        button->setColor(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
        break;
    case ButtonComponent::PRESSED:
        button->setColor(pressedColor.r, pressedColor.g, pressedColor.b, pressedColor.a);
        break;
    }
}
