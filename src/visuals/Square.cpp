#include <jengine/visuals/Square.hpp>
#include <jengine/Renderer.hpp>

Square::Square(unsigned int width, unsigned int height) : width(width), height(height) {}

Square::Square(Vector position, unsigned int width, unsigned int height) : Visual(position), width(width), height(height) {}

Square::~Square() {}

void Square::output()
{
    Renderer *renderer = Renderer::getInstance();
    if (renderer == nullptr)
    {
        return;
    }

    SDL_FRect square = {globalPosition.x, globalPosition.y, float(width), float(height)};

    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRectF(renderer->renderer, &square);
}