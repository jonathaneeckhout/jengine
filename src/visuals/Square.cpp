#include <jengine/visuals/Square.hpp>
#include <jengine/core/Renderer.hpp>

Square::Square(int width, int height) : width(width), height(height) {}

Square::Square(Vector position, int width, int height) : Visual(position), width(width), height(height) {}

Square::~Square() {}

void Square::output()
{
    Renderer *renderer = Renderer::getInstance();
    if (renderer == nullptr)
    {
        return;
    }

    Vector globalPosition = getGlobalPosition();

    SDL_FRect square = {globalPosition.x, globalPosition.y, static_cast<float>(width), static_cast<float>(height)};

    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer->renderer, &square);
}