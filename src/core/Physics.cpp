#include "jengine/core/Physics.hpp"

Physics *Physics::instancePtr = nullptr;

Physics::Physics() : Object()
{
    name = "Physics";
}

Physics::~Physics() {}

Physics *Physics::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Physics();
    }
    return instancePtr;
}

void Physics::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}
