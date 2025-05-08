#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "jengine/core/Game.hpp"

Game *Game::instancePtr = NULL;

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
    removeChild(controls->getId());
    removeChild(renderer->getId());
    removeChild(resources->getId());

    deleteChildren();

    Controls::deleteInstance();
    Renderer::deleteInstance();
    Resources::deleteInstance();

    TTF_Quit();

    SDL_Quit();
}

Game *Game::getInstance()
{
    if (instancePtr == NULL)
    {
        instancePtr = new Game();
    }

    return instancePtr;
}

void Game::deleteInstance()
{
    if (instancePtr != NULL)
    {
        delete instancePtr;
        instancePtr = NULL;
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
