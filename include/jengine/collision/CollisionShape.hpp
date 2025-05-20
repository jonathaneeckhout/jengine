#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <memory>

#include "jengine/entities/Entity.hpp"

class CollisionShape : public Entity
{
public:
    // This is the layer the CollisionShape is in
    uint32_t inLayer = 0x00000001;

    // This is the layer the CollisionShape sees
    uint32_t viewLayer = 0x00000001;

    std::vector<std::function<void(std::weak_ptr<CollisionShape> shape)>> collisionStartHandlers;
    std::vector<std::function<void(std::weak_ptr<CollisionShape> shape)>> collisionEndHandlers;

    CollisionShape(Vector position);
    virtual ~CollisionShape();

    const std::vector<std::weak_ptr<CollisionShape>> getColliders();

    virtual bool collidesWith(const CollisionShape &other) const = 0;

    virtual bool collidesWith(const Vector &point) const = 0;
    virtual bool collidesWithSquare(const class CollisionShapeSquare &square) const = 0;

    void update(float dt) override;

    virtual void __addToGame() override;
    virtual void __removeFromGame() override;

    virtual Vector getCollisionNormal(const CollisionShape &other) const = 0;
    virtual Vector getCollisionNormalSquare(const class CollisionShapeSquare &square) const = 0;

private:
    std::vector<std::weak_ptr<CollisionShape>> colliders;

    void removeCollider(const CollisionShape *shape);

    void triggerStartHandlers(std::vector<std::weak_ptr<CollisionShape>> &addedColliders);
    void triggerEndHandlers(std::vector<std::weak_ptr<CollisionShape>> &removedColliders);
};