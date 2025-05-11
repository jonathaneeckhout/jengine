#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "jengine/core/Game.hpp"

Game *Game::instancePtr = nullptr;

Game::Game() : running(false)
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

    renderer = Renderer::getInstance();

    controls = Controls::getInstance();

    resources = Resources::getInstance();

    controls->onStop = [this]()
    {
        stop();
    };
}

Game::~Game()
{
    Physics::deleteInstance();
    phyics = nullptr;

    Renderer::deleteInstance();
    renderer = nullptr;

    Controls::deleteInstance();
    controls = nullptr;

    Resources::deleteInstance();
    resources = nullptr;

    if (rootObject)
    {
        Object::DeleteObject(rootObject);
        rootObject = nullptr;
    }

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
    if (rootObject == nullptr)
    {
        throw std::runtime_error("Please set a rootObject before running the engine.");
    }

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
    if (object == nullptr)
    {
        return;
    }

    toBedeleted.push_back(object);
}

void Game::input()
{
    phyics->__input();
    renderer->__input();
    controls->__input();
    resources->__input();
    rootObject->__input();
}

void Game::update(float dt)
{
    phyics->__update(dt);
    renderer->__update(dt);
    controls->__update(dt);
    resources->__update(dt);
    rootObject->__update(dt);

    // Remove queued to be deleted objects
    for (auto object : toBedeleted)
    {
        Object *objectParent = object->getParent();
        if (objectParent != nullptr)
        {
            objectParent->removeChild(object);
        }

        Object::DeleteObject(object);
    }

    toBedeleted.clear();
}

void Game::output()
{
    renderer->clear();

    phyics->__output();
    renderer->__output();
    controls->__output();
    resources->__output();
    rootObject->__output();

    renderer->present();
}

void Game::setFPS(float newFPS)
{
    fps = newFPS;
}

void Game::setRootObject(Object *object)
{
    rootObject = object;
}
