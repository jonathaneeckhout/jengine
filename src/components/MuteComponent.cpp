#include "jengine/components/MuteComponent.hpp"
#include "jengine/core/Game.hpp"

MuteComponent::MuteComponent(const std::string &muteKey) : muteKey(muteKey)
{
    mutedCallbackID = Game::getInstance()->controls->addKeyHandler([muteKey](std::string key, bool pressed)
                                                                   {
        if (!pressed) {
            return;
        }

        if(Game::getInstance()->controls->isMapping(muteKey, key)) {
            auto mixer = Game::getInstance()->mixer;
            if(mixer->isMuted()) {
                mixer->unMute();
            } else {
                mixer->mute();
            }
        } });
}

MuteComponent::~MuteComponent()
{
    Game::getInstance()->controls->removeKeyHandler(mutedCallbackID);
}