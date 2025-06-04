#include "jengine/components/TimerComponent.hpp"

TimerComponent::TimerComponent(
    float timeout,
    bool restart,
    std::function<void(void *)> callback,
    void *userdata)
    : timeout(timeout),
      restart(restart),
      callback(callback),
      userdata(userdata) {}

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

        if (callback)
        {
            callback(userdata);
        }
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

void TimerComponent::setCallback(std::function<void(void *)> cb, void *data)
{
    callback = cb;
    userdata = data;
}