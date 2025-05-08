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

    SDL_Rect square = {static_cast<int>(globalPosition.x), static_cast<int>(globalPosition.y), width, height};

    SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer->renderer, &square);
}