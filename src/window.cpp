#include "window.h"
#include <iostream>
#include "util.h"

Playback::Window::Window(std::string name, int w, int h)
    : w(w), h(h), name(std::move(name)), win(nullptr), renderer(nullptr)
{

}

bool Playback::Window::init() 
{
    win = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    RETURN_IF_NULL_OPT(win, false);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); 
    RETURN_IF_NULL_OPT(renderer, false);

    std::cout << "Created window successfully!";
    return true;
}

Playback::Window::~Window() 
{
    if (!(win && renderer)) return;
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    win = nullptr; 
    renderer = nullptr;
}