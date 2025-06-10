#pragma once

#include <functional>

#include "jengine/basics/Object.hpp"

class TimerComponent : public Object
{
public:
    TimerComponent(float timeout = 1.0, bool restart = false);

    void update(float dt) override;

    bool isRunning() { return running; };

    void setTimeout(float newTimeout) { timeout = newTimeout; };
    void setRestart(bool shouldRestart) { restart = shouldRestart; };

    void start();
    void stop();

private:
    float timeout = 0.0;
    bool restart = false;

    bool running = false;
    float offset = 0;
};