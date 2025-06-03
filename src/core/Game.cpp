#include <chrono>
#include <thread>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "jengine/core/Game.hpp"

Game *Game::instancePtr = nullptr;

Game::Game() : running(false),
               randomGenerator(static_cast<unsigned int>(std::time(nullptr))),
               randomDistribution(0.0f, 1.0f)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        throw std::runtime_error("Failed to initialize SDL");
    }

    if (!TTF_Init())
    {
        throw std::runtime_error("Failed to initialize TFF");
    }

    physics = new Physics();

    renderer = new Renderer;

    mixer = new Mixer();

    controls = new Controls();

    resources = new Resources();

    controls->onStop = [this]()
    {
        stop();
    };
}

Game::~Game()
{
    if (rootObject != nullptr)
    {
        rootObject->__cleanup();

        delete rootObject;

        rootObject = nullptr;
    }

    if (oldRootObject != nullptr)
    {
        rootObject->__cleanup();

        delete oldRootObject;

        oldRootObject = nullptr;
    }

    delete physics;
    physics = nullptr;

    delete renderer;
    renderer = nullptr;

    delete mixer;
    mixer = nullptr;

    delete controls;
    controls = nullptr;

    delete resources;
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
    if (rootObject == nullptr)
    {
        throw std::runtime_error("Please set a rootObject before running the engine.");
    }

    running = true;

    const auto frameDuration = std::chrono::duration<double>(1.0 / fps);

    while (running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        __tick(frameDuration.count());

        auto frameEnd = std::chrono::high_resolution_clock::now();

        auto elapsed = frameEnd - frameStart;

        if (elapsed < frameDuration)
        {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }

        auto tickEnd = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration<float>(tickEnd - frameStart);
        actualFPS = 1.0f / duration.count();
    }
}

void Game::__tick(float dt)
{
    input();

    update(dt);

    output();

    checkDeleteObjects();
}

void Game::stop()
{
    running = false;
}

void Game::input()
{
    controls->input();
    rootObject->__input();
}

void Game::update(float dt)
{
    rootObject->__update(dt);
}

void Game::output()
{
    renderer->clear();

    rootObject->__output();

    renderer->present();
}

void Game::checkDeleteObjects()
{
    if (oldRootObject != nullptr)
    {
        oldRootObject->__removeFromGame();

        oldRootObject->__cleanup();

        delete oldRootObject;

        oldRootObject = nullptr;
    }

    rootObject->__checkDeleteObjects();
}

void Game::setRootObject(Object *object)
{
    oldRootObject = rootObject;

    rootObject = object;
    rootObject->__addToGame();
}

float Game::getRandomFloat()
{
    return randomDistribution(randomGenerator);
}

bool Game::shouldHappen(float probability)
{
    return getRandomFloat() <= probability;
}
