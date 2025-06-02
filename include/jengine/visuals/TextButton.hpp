#pragma once

#include "jengine/visuals/Button.hpp"
#include "jengine/visuals/Text.hpp"

class TextButton : public Button
{
public:
    TextButton(Vector position, Vector size, const std::string &text, unsigned int textSize, const std::string &textResourceName);
    ~TextButton();

    void __init() override;

    void setText(const std::string &newText);

protected:
    std::string text;
    unsigned int textSize;
    std::string textResourceName;

    Text *textField = nullptr;
};