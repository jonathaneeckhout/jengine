#pragma once

#include <SDL3/SDL.h>

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"
#include "jengine/components/SquareComponent.hpp"

class ButtonComponent : public Object
{
public:
    ButtonComponent(Vector position, Vector size);

    void setIdle();
    void setSelected();
    void setPressed();

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setSelectedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setPressedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
    Vector size = Vector(32.0, 32.0);

    enum State
    {
        IDLE,
        SELECTED,
        PRESSED
    };

    State state = IDLE;

    SDL_Color color = {32, 32, 32, 255};
    SDL_Color selectedColor = {128, 128, 128, 255};
    SDL_Color pressedColor = {196, 196, 196, 255};

    SquareComponent *button = nullptr;

    void updateColor();
};