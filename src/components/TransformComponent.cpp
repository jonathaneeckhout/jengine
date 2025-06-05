#include <jengine/basics/Object.hpp>
#include "jengine/components/TransformComponent.hpp"

TransformComponent::TransformComponent(Vector position, Vector velocity) : velocity(velocity), position(position)
{
    setName("TransformComponent");
}

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

    auto parent = getParent()->getParent();
    if (parent == nullptr)
    {
        globalPosition = position;
    }
    else
    {
        auto parentTransform = parent->getChild<TransformComponent>();
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
