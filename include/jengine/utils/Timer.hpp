#pragma once

#include "jengine/basics/Object.hpp"
#include "jengine/components/TimerComponent.hpp"

namespace jengine
{
    namespace utils
    {
        Object *createTimer(float timeout = 1.0,
                            bool restart = false,
                            std::function<void(void *)> callback = nullptr,
                            void *userdata = nullptr);
    }
}