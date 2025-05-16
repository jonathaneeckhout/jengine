#include "jengine/systems/Timer.hpp"

Timer::Timer(float timeout) : timeout(timeout) {};

Timer::~Timer() {};

void Timer::update(float dt)
{
    if (running)
    {
        offset += dt;

        if (offset >= timeout)
        {
            // Restart the timer if needed
            running = restart;
            offset = 0.0f;

            if (callback)
            {
                callback(userdata);
            }
        }
    }
}

void Timer::start()
{
    running = true;
    offset = 0.0f;
}

void Timer::stop()
{
    running = false;
    offset = 0.0f;
}

void Timer::setCallback(std::function<void(void *)> cb, void *data)
{
    callback = cb;
    userdata = data;
}

bool Timer::isRunning()
{
    return running;
};