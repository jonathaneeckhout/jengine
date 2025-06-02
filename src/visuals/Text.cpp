#include <SDL3_ttf/SDL_ttf.h>

#include "jengine/visuals/Text.hpp"
#include "jengine/core/Resources.hpp"
#include "jengine/core/Renderer.hpp"

Text::Text(Vector position, const std::string &text, unsigned int size, const std::string &resourceName) : Visual(position)
{
    auto resources = Resources::getInstance();

    auto fontIO = resources->getResource(resourceName);
    if (fontIO == nullptr)
    {
        return;
    }

    font = TTF_OpenFontIO(fontIO, false, size);
    if (font == NULL)
    {
        font = nullptr;
        return;
    }

    setText(text);
}

Text::~Text()
{
    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (surface != nullptr)
    {
        SDL_DestroySurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Text::output()
{
    Renderer *renderer = Renderer::getInstance();

    Vector position = getGlobalPosition();

    SDL_FRect rect;

    if (centered)
    {
        rect = {position.x - (surface->w / 2), position.y - (surface->h / 2), float(surface->w), float(surface->h)};
    }
    else
    {
        rect = {position.x, position.y, float(surface->w), float(surface->h)};
    }

    SDL_RenderTexture(renderer->renderer, texture, NULL, &rect);
}

void Text::setText(const std::string &text)
{
    if (surface != nullptr)
    {
        SDL_DestroySurface(surface);
        surface = nullptr;
    }

    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
    if (surface == NULL)
    {
        surface = nullptr;
        return;
    }

    texture = SDL_CreateTextureFromSurface(Renderer::getInstance()->renderer, surface);
    if (texture == NULL)
    {
        texture = nullptr;

        SDL_DestroySurface(surface);
        surface = nullptr;

        return;
    }
}