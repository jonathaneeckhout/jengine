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
}

Game::~Game() {}

void Game::init()
{
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

void Game::cleanup()
{
    removeChild(phyics);
    removeChild(renderer);
    removeChild(controls);
    removeChild(resources);

    deleteChildren();

    Physics::deleteInstance();
    phyics = nullptr;

    Renderer::deleteInstance();
    renderer = nullptr;

    Controls::deleteInstance();
    controls = nullptr;

    Resources::deleteInstance();
    resources = nullptr;

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
    if (object == nullptr) {
        return;
    }

    toBedeleted.push_back(object);
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
    for (auto object : toBedeleted)
    {
        Object *objectParent = object->getParent();
        if (objectParent != nullptr)
        {
            objectParent->deleteChild(object);
        } else {
            delete object;
        }
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
