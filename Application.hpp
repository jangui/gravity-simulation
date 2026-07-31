
#pragma once

#include "platform/SdlContext.hpp"
#include "platform/Window.hpp"
#include "render/Renderer.hpp"

class Application {
public:
    Application();

    Window window_; // todo make private
private:
    SdlContext sdl_;
    //Window window_;
    Renderer renderer_;
};
