#pragma once

#include "Event.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include <stdexcept>

#include "jengine/basics/Event.hpp"

class Events
{
public:
    template <typename... Args>
    void createEvent(const std::string &name)
    {
        if (events.find(name) != events.end())
        {
            throw std::runtime_error("Event already exists: " + name);
        }

        events[name] = std::make_unique<Event<Args...>>(name);
    }

    void deleteEvent(const std::string &name)
    {
        events.erase(name);
    }

    template <typename... Args>
    int addHandler(const std::string &name, std::function<void(Args...)> handler)
    {
        EventBase *baseEvent = getEvent(name);

        Event<Args...> *event = dynamic_cast<Event<Args...> *>(baseEvent);
        if (event == nullptr)
        {
            throw std::runtime_error("Handler type mismatch for event: " + name);
        }

        return event->addHandler(std::move(handler));
    }

    void removeHandler(const std::string &name, int handlerId)
    {
        EventBase *baseEvent = getEvent(name);

        if (baseEvent == nullptr)
        {
            throw std::runtime_error("Event not found: " + name);
        }

        baseEvent->removeHandler(handlerId);
    }

    template <typename... Args>
    void trigger(const std::string &name, Args... args)
    {
        EventBase *baseEvent = getEvent(name);

        Event<Args...> *event = dynamic_cast<Event<Args...> *>(baseEvent);
        if (event == nullptr)
        {
            throw std::runtime_error("Trigger type mismatch for event: " + name);
        }

        event->trigger(std::forward<Args>(args)...);
    }

    void process(const std::string &name)
    {
        EventBase *baseEvent = getEvent(name);

        if (baseEvent == nullptr)
        {
            throw std::runtime_error("Event not found: " + name);
        }

        baseEvent->process();
    }

    void processAll()
    {
        for (auto &pair : events)
        {
            pair.second->process();
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<EventBase>> events;

    EventBase *getEvent(const std::string &name)
    {
        auto it = events.find(name);

        if (it == events.end())
        {
            return nullptr;
        }

        return it->second.get();
    }
};