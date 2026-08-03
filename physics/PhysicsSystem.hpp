
#pragma once

#include <vector>

#include "PhysicsTypes.hpp"
#include "PhysicsBodyHandle.hpp"
#include "../math/Vec2.hpp"

class PhysicsSystem {
public:
    PhysicsSystem();
    void updateBodies(double deltaTime);
    PhysicsBodyHandle createBody(const Vec2& position, const Vec2& velocity, double mass);
    const PhysicsBody& body(const PhysicsBodyHandle handle);
    ~PhysicsSystem();
    PhysicsSystem(const PhysicsSystem&) = delete; // delete copy constructor
    PhysicsSystem& operator=(const PhysicsSystem&) = delete; // delete assigment constructor
private:
    std::vector<PhysicsBody> bodies_;
    std::vector<PhysicsBody> nextBodies_;

};
