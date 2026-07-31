
#pragma once

#include <string>

#include <string>

#include <SDL.h>

struct WindowConfig {
    std::string title = "Gravity Simulation";
    int width = 1200;
    int height = 900;
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
};

class Window {
public:
    explicit Window(const WindowConfig& config);

    ~Window();

   // delete copy constructor
   Window(const Window&) = delete;
   // delete assignment operator
   Window& operator=(const Window&) = delete;

    SDL_Window *window_ = nullptr; // todo make private
private:
    //SDL_Window *window_ = nullptr;
};
