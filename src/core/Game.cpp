#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "jengine/core/Game.hpp"

Game *Game::instancePtr = nullptr;

Game::Game() : Object(), running(false)
{
    name = "Game";

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL");
    }

    if (TTF_Init() < 0)
    {
        throw std::runtime_error("Failed to initialize TFF");
    }

    phyics = Physics::getInstance();

    addChild(phyics);

    renderer = Renderer::getInstance();

    addChild(renderer);

    controls = Controls::getInstance();

    addChild(controls);

    resources = Resources::getInstance();

    addChild(resources);

    controls->onStop = [this]()
    {
        stop();
    };
}

Game::~Game()
{
    removeChild(phyics->getId());
    removeChild(renderer->getId());
    removeChild(controls->getId());
    removeChild(resources->getId());

    deleteChildren();

    Physics::deleteInstance();
    Renderer::deleteInstance();
    Controls::deleteInstance();
    Resources::deleteInstance();

    TTF_Quit();

    SDL_Quit();
}

Game *Game::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Game();
    }

    return instancePtr;
}

void Game::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}

void Game::run()
{
    running = true;

    const auto frameDuration = std::chrono::duration<double>(1.0 / fps);

    while (running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        input();

        update(frameDuration.count());

        output();

        auto frameEnd = std::chrono::high_resolution_clock::now();

        auto elapsed = frameEnd - frameStart;

        if (elapsed < frameDuration)
        {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}

void Game::stop()
{
    running = false;
}

void Game::queueDeleteObject(Object *object)
{
    ToBeDeleted *ripObject = new ToBeDeleted();
    ripObject->id = object->getId();

    Object *current = object;
    while (Object *parent = current->getParent())
    {
        ripObject->parents.push_front(parent->getId());

        current = parent;
    }

    toBedeleted.push_back(ripObject);
}

void Game::input()
{
    for (auto &child : getChildren())
    {
        child->__input();
    }
}

void Game::update(float dt)
{
    for (auto &child : getChildren())
    {
        child->__update(dt);
    }

    // Remove queued to be deleted objects
    for (auto &ripObject : toBedeleted)
    {
        Object *ripObjectParent = this;
        for (auto &parentId : ripObject->parents)
        {
            if (parentId == getId())
            {
                continue;
            }

            ripObjectParent = ripObjectParent->getChild(parentId);
            if (ripObjectParent == nullptr)
            {
                break;
            }
        }

        if (ripObjectParent != nullptr)
        {
            ripObjectParent->deleteChild(ripObject->id);
        }

        delete ripObject;
    }

    toBedeleted.clear();
}

void Game::output()
{
    renderer->clear();

    for (auto &child : getChildren())
    {
        child->__output();
    }

    renderer->present();
}

void Game::setFPS(float newFPS)
{
    fps = newFPS;
}
