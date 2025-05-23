#pragma once

#include "jengine/visuals/Text.hpp"

class Label : public Text
{
public:
    Label(Vector position, const std::string &text, const std::string &fontName, unsigned int size);
    ~Label();

private:
    void output() override;
};