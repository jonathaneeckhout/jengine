#include "jengine/visuals/Label.hpp"
#include "jengine/core/Renderer.hpp"

Label::Label(Vector position, const std::string &text, const std::string &fontName, unsigned int size) : Text(position, text, fontName, size) {}

Label::~Label() {}

void Label::output()
{
    Renderer *renderer = Renderer::getInstance();

    Vector position = getPosition();

    SDL_FRect rect = {position.x - float(surface->w) / 2, position.y, float(surface->w), float(surface->h)};
    SDL_RenderTexture(renderer->renderer, texture, NULL, &rect);
}