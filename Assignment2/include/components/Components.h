#pragma once

enum class ComponentID {
    UNDEFINED = -1,
    INPUT = 0,
    POSITION = 1,
    VELOCITY = 2,
    TTL = 3,
    COLLIDER=4,
    GRAPHICS=5,
    HEALTH=6,
    LOGIC=7
    //Add more components as needed
};

class Component {
public:
    virtual ComponentID getID() const = 0;
};

