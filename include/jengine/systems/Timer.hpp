#pragma once

#include <functional>

#include "jengine/Object.hpp"

class Timer : public Object
{
public:
    float timeout = 0.0;
    bool restart = false;

    Timer(float timeout);
    ~Timer();

    void update(float dt) override;

    void start();
    void stop();

    bool isRunning();

    void setCallback(std::function<void(void *)> cb, void *data = nullptr);

private:
    bool running = false;
    float offset = 0;

    std::function<void(void *)> callback;
    void *userdata = nullptr;
};