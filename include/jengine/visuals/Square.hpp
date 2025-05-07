#pragma once

#include <jengine/visuals/Visual.hpp>

class Square : public Visual
{
public:
    unsigned int width = 0;
    unsigned int height = 0;

    Square(unsigned int width, unsigned int height);

    Square(Vector position, unsigned int width, unsigned int height);

    ~Square();

    void output() override;
};