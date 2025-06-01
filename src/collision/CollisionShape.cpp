#include "jengine/collision/CollisionShape.hpp"
#include "jengine/core/Physics.hpp"

CollisionShape::CollisionShape(Vector position) : Entity(position) {}

CollisionShape::~CollisionShape() {}

void CollisionShape::__addToGame()
{
    Entity::__addToGame();

    Physics *physics = Physics::getInstance();

    physics->addCollisionShape(this);
}

void CollisionShape::__removeFromGame()
{
    Physics *physics = Physics::getInstance();

    physics->removeCollisionShape(getId());

    for (auto &collider : colliders)
    {

        collider->removeCollider(this);
    }

    Entity::__removeFromGame();

    triggerEndHandlers(colliders);
}

void CollisionShape::update(float)
{
    Physics *physics = Physics::getInstance();

    std::vector<CollisionShape *> newColliders = physics->checkCollision(*this);

    std::vector<CollisionShape *> removedColliders;
    for (const auto &currentCollider : colliders)
    {
        bool stillPresent = false;

        for (const auto &newCollider : newColliders)
        {
            if (newCollider == currentCollider)
            {
                stillPresent = true;
                break;
            }
        }

        if (!stillPresent)
        {
            removedColliders.push_back(currentCollider);
        }
    }

    std::vector<CollisionShape *> addedColliders;
    for (const auto &newCollider : newColliders)
    {
        bool alreadyPresent = false;

        for (const auto &currentCollider : colliders)
        {
            if (currentCollider == newCollider)
            {
                alreadyPresent = true;
                break;
            }
        }

        if (!alreadyPresent)
        {
            addedColliders.push_back(newCollider);
        }
    }

    // Replace current colliders with new ones
    colliders = newColliders;

    triggerEndHandlers(removedColliders);
    triggerStartHandlers(addedColliders);
}

void CollisionShape::removeCollider(const CollisionShape *shape)
{
    auto it = std::remove_if(colliders.begin(), colliders.end(),
                             [shape](CollisionShape *ptr)
                             {
                                 return ptr == shape;
                             });

    if (it != colliders.end())
    {
        colliders.erase(it, colliders.end());
    }
}

void CollisionShape::triggerStartHandlers(const std::vector<CollisionShape *> &addedColliders)
{
    for (auto &collider : addedColliders)
    {
        for (auto &handler : collisionStartHandlers)
        {
            handler(collider);
        }
    }
}

void CollisionShape::triggerEndHandlers(const std::vector<CollisionShape *> &removedColliders)
{
    for (auto &collider : removedColliders)
    {
        for (auto &handler : collisionEndHandlers)
        {
            handler(collider);
        }
    }
}
