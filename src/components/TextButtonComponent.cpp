#include "jengine/components/TextButtonComponent.hpp"

TextButtonComponent::TextButtonComponent(
    Vector position,
    Vector size,
    const std::string &text,
    unsigned int textSize,
    const std::string &textResourceName)
{
    buttonComp = new ButtonComponent(position, size);
    addChild(buttonComp);

    textComp = new TextComponent(position - size / 2, text, textSize, textResourceName);
    textComp->centered = true;
    addChild(textComp);

    events.createEvent<>("onPressed");
    events.createEvent<>("onReleased");

    std::function<void(void)> pressedAction = [this]
    {
        events.trigger("onPressed");
    };

    events.addHandler("onPressed", pressedAction);

    std::function<void(void)> releasedAction = [this]
    {
        events.trigger("onReleased");
    };

    events.addHandler("onReleased", releasedAction);
}
