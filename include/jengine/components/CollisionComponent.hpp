#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

#include "jengine/components/Component.hpp"
#include "jengine/basics/Vector.hpp"
#include "jengine/components/TransformComponent.hpp"

class CollisionComponent : public Component
{
public:
    uint32_t inLayer = 0x00000001;
    uint32_t viewLayer = 0x00000001;

    CollisionComponent(TransformComponent *transform);

    virtual bool collidesWith(const CollisionComponent &other) const = 0;
    virtual bool collidesWith(const Vector &point) const = 0;

    int addCollisionHandler(std::function<void(Object *object, bool collides)> handler);
    void removeCollisionHandler(int id);

private:
    TransformComponent *transform = nullptr;

    int nextHandlerId = 1;
    std::unordered_map<int, std::function<void(Object *, bool)>> collisionHandlers;
};