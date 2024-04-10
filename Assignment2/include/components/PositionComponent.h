#pragma once
#include "../utils/Vector2.h"
#include "Components.h"

class PositionComponent : public Component {
private:
    Vector2f position;

public:
    PositionComponent(float x = 0.0f, float y = 0.0f) : position(x, y) {}

    const Vector2f& getPosition() const {
        return position;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    ComponentID getID() const override { return ComponentID::POSITION; }
};
