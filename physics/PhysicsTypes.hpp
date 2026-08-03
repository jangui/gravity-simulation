
#pragma once

#include "../math/Vec2.hpp"

struct PhysicsBody {
    Vec2 position;
    Vec2 velocity;
    double mass = 0.0;
};