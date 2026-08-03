
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
    [[nodiscard]] SDL_Window* getWindow() const;
    ~Window();
    Window(const Window&) = delete; // delete copy constructor
    Window& operator=(const Window&) = delete; // delete assignment operator
private:
    SDL_Window *window_ = nullptr;
};
