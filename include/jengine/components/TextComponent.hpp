#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"

class TextComponent : public Object
{
public:
    bool centered = false;

    TextComponent(Vector position, const std::string &text, unsigned int size, const std::string &resourceName);
    ~TextComponent();

    void output() override;

    void setText(const std::string &text);

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { color = {r, g, b, a}; }

private:
    TransformComponent *transform = nullptr;

    SDL_Color color = {255, 255, 255, 255};

    TTF_Font *font = nullptr;

    SDL_Surface *surface = nullptr;

    SDL_Texture *texture = nullptr;
};