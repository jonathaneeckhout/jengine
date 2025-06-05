#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <memory>
#include <string>
#include <utility>

#include "jengine/basics/EventBase.hpp"

template <typename... Args>
class Event : public EventBase
{
public:
    Event(const std::string &name) : name(name) {};

    int addHandler(std::function<void(Args...)> handler)
    {
        int id = nextHandlerID++;
        handlers[id] = std::move(handler);
        return id;
    }

    void removeHandler(int id) override
    {
        handlers.erase(id);
    }

    void trigger(Args... args)
    {
        queue.emplace(std::make_tuple(std::forward<Args>(args)...));
    }

    void process() override
    {
        while (!queue.empty())
        {
            auto args = std::move(queue.front());
            queue.pop();
            for (auto &[_, handler] : handlers)
            {
                std::apply(handler, args);
            }
        }
    }

private:
    std::string name;
    int nextHandlerID = 1;
    std::unordered_map<int, std::function<void(Args...)>> handlers;
    std::queue<std::tuple<Args...>> queue;
};
