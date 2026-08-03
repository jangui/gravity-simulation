
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::updateBodies(double deltaTime) {
    constexpr double gravitationalConstant = 10000.0;
    constexpr double softening = 1e-10;

    // Keep output buffer aligned with the current state buffer
    nextBodies_.resize(bodies_.size());

    for (std::size_t i = 0; i < bodies_.size(); ++i) {
        const PhysicsBody& body = bodies_[i];

        Vec2 totalAcceleration{};

        for (std::size_t j = 0; j < bodies_.size(); ++j) {
            if (i == j) { continue; }

            const PhysicsBody& other = bodies_[j];

            /*

            vectorized force equation:
            F = (G(m1 * m2) / distance^2) * direction_vector

            Goal: solve for vectorized acceleration

            F = m1 * a
            direction_vector = displacement_vector / distance
            m1 * a = (G(m1*m2) / distance^2 ) * ( displacement_vector / distance )
            m1 * a = ( G * (m1*m2) / distance^3 ) * displacement_vector
            a = ( G*m2 / distance^3 ) * displacement_vector

            thus, our vectorized acceleration equation is:
            a = ( G*m2 / distance^3 ) * displacement_vector

             */

            // calc displacement vector
            const Vec2 displacement = other.position - body.position;

            // calc distance cubed
            const double distance = displacement.length();
            double distanceCubed = distance * distance * distance;
            distanceCubed += softening; // add softening to avoid division by 0 error

            // calculate acc and sum to total acceleration
            const double accelerationScale = (gravitationalConstant * other.mass / distanceCubed);
            totalAcceleration += displacement * accelerationScale;
        }

        // update body's velocity and position using the calculated acceleration
        PhysicsBody updatedBody = body;
        updatedBody.velocity += totalAcceleration * deltaTime;
        updatedBody.position += updatedBody.velocity * deltaTime;

        // save updated body
        nextBodies_[i] = updatedBody;
    }

    // after all bodies updated, swap updated bodies into current bodies vector
    bodies_.swap(nextBodies_);
}

PhysicsBodyHandle PhysicsSystem::createBody(const Vec2& position, const Vec2& velocity, double mass) {
    const auto index = static_cast<uint32_t>(bodies_.size());

    PhysicsBody body = {position, velocity, mass};

    bodies_.push_back(body);
    nextBodies_.push_back(body);

    return PhysicsBodyHandle{index, 0};
}

const PhysicsBody& PhysicsSystem::body(const PhysicsBodyHandle handle) {
   return bodies_[handle.index];
}

PhysicsSystem::~PhysicsSystem() {}