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
            return new SquareComponent(position, size, color);
        }

        Object *createLabel(Vector position, const std::string &text, unsigned int size, const std::string &resourceName)
        {
            auto obj = new Object();
            obj->setName("Label");

            auto textComponent = new TextComponent(position, text, size, resourceName);
            obj->addChild(textComponent);

            return obj;
        }
    }
}