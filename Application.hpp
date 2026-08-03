
#pragma once

#include "physics/PhysicsSystem.hpp"
#include "platform/SdlContext.hpp"
#include "platform/Window.hpp"
#include "render/Renderer.hpp"

class Application {
public:
    Application();
    void run();
    void createBody(double mass, double radius, double x, double y, double vx, double vy, SDL_Color color);
    ~Application();
private:
    PhysicsSystem physics_;
    SdlContext sdl_;
    Window window_;
    Renderer renderer_;
};
