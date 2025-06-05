#include "jengine/factories/Visuals.hpp"
#include "jengine/basics/Object.hpp"
#include "jengine/components/TransformComponent.hpp"
#include "jengine/components/SquareComponent.hpp"
#include "jengine/components/TextComponent.hpp"

namespace jengine
{
    namespace visuals
    {
        Object *createSquare(Vector position, Vector size, SDL_Color color)
        {
            auto obj = new Object();
            obj->setName("Square");

            auto transform = new TransformComponent(position);
            obj->addChild(transform);

            auto square = new SquareComponent(transform, size, color);
            obj->addChild(square);

            return obj;
        }

        Object *createLabel(Vector position, const std::string &text, unsigned int size, const std::string &resourceName)
        {
            auto obj = new Object();
            obj->setName("Label");

            auto transform = new TransformComponent(position);
            obj->addChild(transform);

            auto textComponent = new TextComponent(transform, text, size, resourceName);
            obj->addChild(textComponent);

            return obj;
        }
    }
}