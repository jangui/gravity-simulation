#pragma once

#include <vector>

#include <SDL.h>

#include "RenderTypes.hpp"
#include "RenderHandles.hpp"
#include "../physics/PhysicsSystem.hpp"

struct RendererConfig {
    int index = -1;
    SDL_RendererFlags flags =
        static_cast<SDL_RendererFlags>(
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
};

class Renderer {
public:
    Renderer(SDL_Window *window, const RendererConfig& config, PhysicsSystem* physicsSystem) ;
    void render();
    void renderPoints();
    void renderRectangles();
    RectangleHandle createRectangle(const PhysicsBodyHandle& body, double width, double height, const SDL_Color& color);
    ~Renderer();
    Renderer(const Renderer&) = delete; // delete copy constructor
    Renderer& operator=(const Renderer&) = delete; // delete assignment operator
private:
    SDL_Renderer *renderer_ = nullptr;
    PhysicsSystem* physicsSystem_ = nullptr;
    std::vector<PointVisual> points_;
    std::vector<RectangleVisual> rectangles_;
};

