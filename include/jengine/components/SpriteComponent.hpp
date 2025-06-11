#pragma once

#include <SDL3/SDL.h>
#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/basics/Vector.hpp"

class SpriteComponent : public Object
{
public:
    bool centered = false;

    SpriteComponent(Vector position, const std::string &resourceName);
    ~SpriteComponent();

    void output() override;

private:
    Vector position;
    TransformComponent *transform = nullptr;

    SDL_Texture *texture = nullptr;
    int texture_width = 0;
    int texture_height = 0;
};
