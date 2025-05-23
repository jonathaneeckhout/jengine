#pragma once

#include <string>
#include <SDL3_ttf/SDL_ttf.h>

#include "jengine/visuals/Visual.hpp"

class Text : public Visual
{
public:
    std::string text = "";

    unsigned int size = 16;

    bool centered = false;
    Text(Vector position, const std::string &text, const std::string &fontName, unsigned int size);
    ~Text();


protected:
    TTF_Font *font = nullptr;

    SDL_Surface *surface = nullptr;

    SDL_Texture *texture = nullptr;

    bool setFont(const std::string &name, unsigned int size);
};