#pragma once

class EventBase
{
public:
    virtual ~EventBase() = default;
    virtual void process() = 0;
    virtual void removeHandler(int handlerId) = 0;
};
