#pragma once

#include <string>
#include <SDL3_ttf/SDL_ttf.h>

#include "jengine/visuals/Visual.hpp"

class Text : public Visual
{
public:
    Text(Vector position, const std::string &text, unsigned int size, const std::string &resourceName);
    ~Text();

    void output() override;

    void setText(const std::string &text);

protected:
    TTF_Font *font = nullptr;

    SDL_Surface *surface = nullptr;

    SDL_Texture *texture = nullptr;
};