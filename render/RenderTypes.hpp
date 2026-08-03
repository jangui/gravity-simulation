
#pragma once

#include <SDL.h>

#include "../physics/PhysicsBodyHandle.hpp"

struct RectangleVisual {
    PhysicsBodyHandle body;
    double width;
    double height;
    SDL_Color color;
};

struct PointVisual {
    int x;
    int y;
    SDL_Color color;
};