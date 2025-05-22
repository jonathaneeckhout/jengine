#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <map>

#include "jengine/basics/Object.hpp"
#include "jengine/basics/Vector.hpp"

class Renderer : public Object
{
public:
    SDL_Window *window;
    static const Vector windowSize;

    SDL_Renderer *renderer;

    std::map<std::string, TTF_Font *> fonts;

    ~Renderer();

    Renderer(const Renderer &) = delete;

    static Renderer *getInstance();
    static void deleteInstance();

    void clear();
    void present();

    void setWindowTitle(std::string title);

private:
    static Renderer *instancePtr;

    Renderer();
};