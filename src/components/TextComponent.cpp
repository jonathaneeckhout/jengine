#include "jengine/components/TextComponent.hpp"
#include "jengine/core/Game.hpp"

TextComponent::TextComponent(
    Vector position,
    const std::string &text,
    unsigned int size,
    const std::string &resourceName)
{
    transform = new TransformComponent(position);
    addChild(transform);

    auto fontIO = Game::getInstance()->resources->getResource(resourceName);
    if (fontIO == nullptr)
    {
        return;
    }

    font = TTF_OpenFontIO(fontIO, true, size);
    if (font == NULL)
    {
        font = nullptr;
        return;
    }

    setText(text);
}

TextComponent::~TextComponent()
{
    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void TextComponent::output()
{
    Vector position = transform->getGlobalPosition();

    SDL_FRect rect;

    if (centered)
    {
        rect = {position.x - (texture_width / 2), position.y - (texture_height / 2), float(texture_width), float(texture_height)};
    }
    else
    {
        rect = {position.x, position.y, float(texture_width), float(texture_height)};
    }

    SDL_RenderTexture(Game::getInstance()->renderer->renderer, texture, NULL, &rect);
}

void TextComponent::setText(const std::string &text)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
    if (surface == NULL)
    {
        return;
    }

    texture_width = surface->w;
    texture_height = surface->h;

    texture = SDL_CreateTextureFromSurface(Game::getInstance()->renderer->renderer, surface);
    if (texture == NULL)
    {
        texture = nullptr;

        SDL_DestroySurface(surface);

        return;
    }

    SDL_DestroySurface(surface);
}