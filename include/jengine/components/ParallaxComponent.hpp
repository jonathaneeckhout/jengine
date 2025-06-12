#pragma once

#include <SDL3/SDL.h>

#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/basics/Vector.hpp"

class ParallaxComponent : public Object
{
public:
    bool centered = false;

    ParallaxComponent(Vector position, Vector direction, float speed, const std::string &resourceName);
    ~ParallaxComponent();

    void update(float dt) override;
    void output() override;

private:
    Vector position;
    float speed = 0.0f;

    TransformComponent *transform = nullptr;

    SDL_Texture *texture = nullptr;
    int texture_width = 0;
    int texture_height = 0;

    int tiles_x = 0;
    int tiles_y = 0;

    Vector scroll_offset{0.0f, 0.0f};
};