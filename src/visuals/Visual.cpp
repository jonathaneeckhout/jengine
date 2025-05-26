#include <jengine/visuals/Visual.hpp>

Visual::Visual() {}

Visual::Visual(Vector position) : Entity(position) {}

Visual::~Visual() {}

void Visual::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    color = {r, g, b, a};
}