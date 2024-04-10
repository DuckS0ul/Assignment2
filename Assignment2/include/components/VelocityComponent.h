#pragma once
#include "../utils/Vector2.h"
#include "Components.h"
#include <memory>

class Entity;

class VelocityComponent : public Component {
private:
    Vector2f velocityDirection;
    float speed;

public:
    VelocityComponent(float spd = 1.0f) : speed(spd), velocityDirection(0.0f, 0.0f) {}

    void setVelocity(float x, float y) {
        velocityDirection.x = x;
        velocityDirection.y = y;
    }

    const Vector2f& getVelocity() const {
        return velocityDirection;
    }

    float getSpeed()
    { 
        return speed; 
    }
    //void update(Entity& entity, float elapsedTime);

    ComponentID getID() const override { return ComponentID::VELOCITY; }
};