#pragma once

#include "jengine/basics/Object.hpp"

class Physics : public Object
{
public:
    ~Physics();

    // Delete copy constructor
    Physics(const Physics &) = delete;

    static Physics *getInstance();
    static void deleteInstance();

private:
    static Physics *instancePtr;

    //TODO: add collisionshapes

    Physics();
};