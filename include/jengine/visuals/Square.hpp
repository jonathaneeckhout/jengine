#pragma once

#include "jengine/visuals/Visual.hpp"

class Square : public Visual
{
public:
    Vector size;

    Square(Vector position, Vector size);

    ~Square();

    void output() override;
};