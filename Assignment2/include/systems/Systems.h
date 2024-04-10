#pragma once
#include "../utils/Bitmask.h"
#include "../entities/Entity.h"

class System {
protected:
    Bitmask componentMask;

public:
    virtual void update(Game* game, Entity* entity, float elapsed) = 0;

    bool validate(Entity* entity) const {
        if (componentMask.getMask() == 0) {
            return false;
        }
        return entity->hasComponent(componentMask);
    }

    void setComponentMask(const Bitmask& mask) {
        componentMask = mask;
    }
};

class TTLSystem : public System 
{
public:
    TTLSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};


class InputSystem : public System
{
public:
    InputSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class MovementSystem : public System
{
public:
    MovementSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class GraphicsSystem : public System
{
public:
    GraphicsSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class ColliderSystem : public System
{
public:
    ColliderSystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};

class GameplaySystem : public System
{
public:
    GameplaySystem();
    void update(Game* game, Entity* entity, float elapsed) override;
};