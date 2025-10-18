#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

namespace Playback
{
    class Window 
    {
    public:
        Window(std::string name, int w, int h);
        bool init();
        ~Window();

    private:
        std::size_t w; 
        std::size_t h;
        std::string name; 
        SDL_Window* win; 
        SDL_Renderer* renderer;
    };
}


#endif // WINDOW_H