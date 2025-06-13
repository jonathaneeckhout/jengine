#include <string>

#include "jengine/basics/Object.hpp"

class MuteComponent : public Object
{
public:
    MuteComponent(const std::string &muteKey);
    ~MuteComponent();

private:
    std::string muteKey;

    int mutedCallbackID = 0;
};