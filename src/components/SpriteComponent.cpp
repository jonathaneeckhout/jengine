#include "jengine/components/SpriteComponent.hpp"

SpriteComponent::SpriteComponent(Vector position, const std::string &resourceName) : position(position)
{
    transform = new TransformComponent(position);
    addChild(transform);
}