#include "jengine/components/TimerComponent.hpp"

TimerComponent::TimerComponent(float timeout, bool restart) : timeout(timeout), restart(restart)
{
    setName("TimerComponent");

    events.createEvent<>("onTimeout");
}

void TimerComponent::update(float dt)
{
    if (!running)
    {
        return;
    }

    offset += dt;

    if (offset >= timeout)
    {
        running = restart;
        offset = 0.0f;

        events.trigger("onTimeout");
    }
}

void TimerComponent::start()
{
    running = true;
    offset = 0.0f;
}

void TimerComponent::stop()
{
    running = false;
    offset = 0.0f;
}