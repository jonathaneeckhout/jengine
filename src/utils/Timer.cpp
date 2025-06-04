#include "jengine/utils/Timer.hpp"

namespace jengine
{
    namespace utils
    {
        Object *createTimer(float timeout,
                            bool restart,
                            std::function<void(void *)> callback,
                            void *userdata)
        {
            auto obj = new Object();

            auto timer = new TimerComponent(timeout, restart, callback, userdata);
            obj->addComponent(timer);

            return obj;
        }
    }

}
