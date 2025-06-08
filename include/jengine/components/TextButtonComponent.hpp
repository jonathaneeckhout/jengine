#pragma once

#include <SDL3/SDL.h>

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"
#include "jengine/components/ButtonComponent.hpp"
#include "jengine/components/TextComponent.hpp"

class TextButtonComponent : public Object
{
public:
    TextButtonComponent(Vector position, Vector size, const std::string &text, unsigned int textSize, const std::string &textResourceName);

    void setIdle() { buttonComp->setIdle(); };
    void setSelected() { buttonComp->setSelected(); };
    void setPressed() { buttonComp->setPressed(); };

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { buttonComp->setColor(r, g, b, a); };
    void setSelectedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { buttonComp->setSelectedColor(r, g, b, a); };
    void setPressedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { buttonComp->setPressedColor(r, g, b, a); };

    void setText(const std::string &text) { textComp->setText(text); };

private:
    ButtonComponent *buttonComp = nullptr;
    TextComponent *textComp = nullptr;
};