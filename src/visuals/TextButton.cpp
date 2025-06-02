#include "jengine/visuals/TextButton.hpp"
#include "jengine/core/Game.hpp"

TextButton::TextButton(Vector position, Vector size, const std::string &text, unsigned int textSize, const std::string &textResourceName) : Button(position, size), text(text), textSize(textSize), textResourceName(textResourceName) {}

TextButton::~TextButton() {}

void TextButton::__init()
{
    Button::__init();

    textField = Game::create<Text>(size / 2, text, textSize, textResourceName);
    textField->centered = true;

    addChild(textField);
}

void TextButton::setText(const std::string &newText)
{
    text = newText;

    textField->setText(newText);
}
