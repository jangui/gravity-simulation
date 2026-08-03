
#include "Window.hpp"

#include <stdexcept>
#include <string>

#include <SDL.h>

Window::Window(const WindowConfig& config) {
    window_ = SDL_CreateWindow(
        config.title.c_str(),
        100,
        100,
        config.width,
        config.height,
        config.flags
        );

    if (window_ == nullptr) {
        throw std::runtime_error(
            std::string("SDL_CreateWindow Error: ") + SDL_GetError()
        );
    }
}

SDL_Window* Window::getWindow() const {
    return window_;
}

Window::~Window() {
    SDL_DestroyWindow(window_);
}
