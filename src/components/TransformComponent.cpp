#include <jengine/basics/Object.hpp>
#include "jengine/components/TransformComponent.hpp"

TransformComponent::TransformComponent(Vector position, Vector velocity) : velocity(velocity), position(position) {}

void TransformComponent::setPosition(Vector newPosition)
{
    dirty = true;
    position = newPosition;
}

void TransformComponent::sync(bool shouldDirty)
{
    dirty |= shouldDirty;

    if (!dirty)
    {
        return;
    }

    updateGlobalPosition();
}

const Vector &TransformComponent::getGlobalPosition()
{
    if (dirty)
    {
        updateGlobalPosition();
    }

    return globalPosition;
};

void TransformComponent::updateGlobalPosition()
{
    dirty = false;

    auto parent = owner->getParent();
    if (parent == nullptr)
    {
        globalPosition = position;
    }
    else
    {
        auto parentTransform = parent->getComponent<TransformComponent>();
        if (parentTransform == nullptr)
        {
            globalPosition = position;
        }
        else
        {
            globalPosition = parentTransform->getGlobalPosition() + position;
        }
    }
}
