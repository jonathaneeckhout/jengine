#include "jengine/visuals/Text.hpp"
#include "jengine/core/Resources.hpp"
#include "jengine/core/Renderer.hpp"

Text::Text(Vector position, const std::string &text, const std::string &fontName, unsigned int size)
    : Visual(position), text(text), font(nullptr), surface(nullptr), texture(nullptr)
{
    setFont(fontName, size);
}

Text::~Text()
{
    if (font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (surface)
    {
        SDL_DestroySurface(surface);
        surface = nullptr;
    }
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

bool Text::setFont(const std::string &name, unsigned int size)
{
    auto &fonts = Resources::getInstance()->fonts;
    auto it = fonts.find(name);
    if (it == fonts.end())
    {
        return false;
    }

    if (surface)
    {
        SDL_DestroySurface(surface);
        surface = nullptr;
    }
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    const auto &fontData = it->second;
    SDL_IOStream *stream = SDL_IOFromConstMem(fontData.data(), fontData.size());
    if (!stream)
    {
        return false;
    }

    font = TTF_OpenFontIO(stream, 1, size); // SDL_ttf takes ownership of stream
    if (!font)
    {
        font = nullptr;
        return false;
    }

    surface = TTF_RenderText_Solid_Wrapped(font, text.c_str(), text.length(), color, 6);
    if (!surface)
    {
        surface = nullptr;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(Renderer::getInstance()->renderer, surface);
    return texture != nullptr;
}
