#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <map>

#include "jengine/basics/Vector.hpp"

class Renderer
{
public:
    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;

    std::map<std::string, TTF_Font *> fonts;

    Renderer();
    ~Renderer();

    void clear();
    void present();

    Vector getWindowSize() { return windowSize; }
    void setWindowSize(Vector newSize);

    void setWindowTitle(std::string title);

private:
    Vector windowSize = {800.0, 600.0};
};