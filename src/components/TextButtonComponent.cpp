#include "jengine/components/TextButtonComponent.hpp"
#include "jengine/components/TransformComponent.hpp"

TextButtonComponent::TextButtonComponent(
    Vector position,
    Vector size,
    const std::string &text,
    unsigned int textSize,
    const std::string &textResourceName)
{
    auto transform = new TransformComponent(position);
    addChild(transform);

    buttonComp = new ButtonComponent(Vector(), size);
    addChild(buttonComp);

    textComp = new TextComponent(size / 2, text, textSize, textResourceName);
    textComp->centered = true;
    addChild(textComp);

    events.createEvent<>("onPressed");
    events.createEvent<>("onReleased");

    std::function<void(void)> pressedAction = [this]
    {
        events.trigger("onPressed");
    };

    buttonComp->addEventHandler("onPressed", pressedAction);

    std::function<void(void)> releasedAction = [this]
    {
        events.trigger("onReleased");
    };

    buttonComp->addEventHandler("onReleased", releasedAction);
}
