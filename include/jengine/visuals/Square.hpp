#pragma once

#include "jengine/visuals/Visual.hpp"

class Square : public Visual
{
public:
    int width = 0;
    int height = 0;

    Square(int width, int height);

    Square(Vector position, int width, int height);

    ~Square();

    void output() override;
};