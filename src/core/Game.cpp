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

    phyics = Physics::getInstance();

    renderer = Renderer::getInstance();

    mixer = Mixer::getInstance();

    controls = Controls::getInstance();

    resources = Resources::getInstance();

    controls->onStop = [this]()
    {
        stop();
    };
}

Game::~Game()
{
    if (rootObject != nullptr)
    {
        rootObject->__removeFromGame();
        rootObject->__cleanup();
        rootObject = nullptr;
    }

    if (oldRootObject != nullptr)
    {
        oldRootObject->__removeFromGame();
        oldRootObject->__cleanup();
        oldRootObject = nullptr;
    }

    Physics::deleteInstance();
    phyics = nullptr;

    Renderer::deleteInstance();
    renderer = nullptr;

    Mixer::deleteInstance();
    mixer = nullptr;

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

        auto duration = std::chrono::duration<float>(tickEnd - frameStart); // duration in seconds (float)
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

void Game::checkDeleteObjects()
{
    if (oldRootObject != nullptr)
    {
        oldRootObject->__removeFromGame();
        oldRootObject->__cleanup();
        oldRootObject = nullptr;
    }

    rootObject->__checkDeleteObjects();
}

void Game::setFPS(float newFPS)
{
    fps = newFPS;
}

float Game::getFPS()
{
    return actualFPS;
}

void Game::setRootObject(std::shared_ptr<Object> object)
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
