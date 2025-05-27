#pragma once

#include <memory>

#include "jengine/visuals/Visual.hpp"
#include "jengine/visuals/Square.hpp"

class Button : public Visual
{
public:
    Button(Vector position, Vector size);
    ~Button();

    void init() override;

    void setIdle();
    void setSelected();
    void setPressed();

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    void setSelectedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setPressColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

protected:
    enum State
    {
        IDLE,
        SELECTED,
        PRESSED
    };

    State state = IDLE;

    Vector size = Vector(32.0, 32.0);

    Vector margin = Vector(2.0, 2.0);

    SDL_Color selectedColor = {128, 128, 128, 255};
    SDL_Color pressColor = {196, 196, 196, 255};

    std::shared_ptr<Square> body;

    void updateColor();
};