#include "jengine/components/TextComponent.hpp"
#include "jengine/core/Game.hpp"

TextComponent::TextComponent(
    Vector position,
    const std::string &text,
    unsigned int size,
    const std::string &resourceName)
{
    transform =  new TransformComponent(position);
    addChild(transform);

    auto fontIO = Game::getInstance()->resources->getResource(resourceName);
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

TextComponent::~TextComponent()
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

void TextComponent::output()
{
    Vector position = transform->getGlobalPosition();

    SDL_FRect rect;

    if (centered)
    {
        rect = {position.x - (surface->w / 2), position.y - (surface->h / 2), float(surface->w), float(surface->h)};
    }
    else
    {
        rect = {position.x, position.y, float(surface->w), float(surface->h)};
    }

    SDL_RenderTexture(Game::getInstance()->renderer->renderer, texture, NULL, &rect);
}

void TextComponent::setText(const std::string &text)
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

    texture = SDL_CreateTextureFromSurface(Game::getInstance()->renderer->renderer, surface);
    if (texture == NULL)
    {
        texture = nullptr;

        SDL_DestroySurface(surface);
        surface = nullptr;

        return;
    }
}