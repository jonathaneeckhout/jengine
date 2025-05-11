#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "jengine/entities/Entity.hpp"

class CollisionShape : public Entity
{
public:
    // This is the layer the CollisionShape is in
    uint32_t inLayer = 0x0001;

    // This is the layer the CollisionShape sees
    uint32_t viewLayer = 0x0001;

    std::vector<CollisionShape *> colliders;

    std::vector<std::function<void(CollisionShape *shape)>> collisionStartHandlers = {};
    std::vector<std::function<void(CollisionShape *shape)>> collisionEndHandlers = {};

    CollisionShape(Vector position);
    virtual ~CollisionShape();

    virtual bool collidesWith(const CollisionShape &other) const = 0;

    virtual bool collidesWith(const Vector &point) const = 0;
    virtual bool collidesWithSquare(const class CollisionShapeSquare &square) const = 0;

    void update(float dt) override;

    void cleanup() override;

private:
    void removeCollider(CollisionShape *shape);

    void triggerStartHandlers(std::vector<CollisionShape *> &addedColliders);
    void triggerEndHandlers(std::vector<CollisionShape *> &removedColliders);
};