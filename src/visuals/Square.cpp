#include <jengine/visuals/Square.hpp>
#include <jengine/core/Renderer.hpp>

Square::Square(Vector position, Vector size) : Visual(position), size(size) {}

Square::~Square() {}

void Square::output()
{
    Renderer *renderer = Renderer::getInstance();
    if (renderer == nullptr)
    {
        return;
    }

    Vector globalPosition = getGlobalPosition();

    SDL_FRect square = {globalPosition.x, globalPosition.y, size.x, size.y};

    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer->renderer, &square);
}