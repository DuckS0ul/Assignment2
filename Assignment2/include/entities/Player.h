#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h"
#include "../components/VelocityComponent.h"

class Fire;
class PlayerInputHandler;
class InputComponent;
class GraphicsComponent;
class SpriteGraphicComponent;
class SpriteSheetGraphicComponent;
class ColliderComponent;
class PlayerStateComponent;

class Player : public Entity {
public:
    const float playerSpeed = 100.f;
    const int startingHealth = 60;
    const int maxHealth = 100;

    Player();
    virtual ~Player();

    void update(Game* game, float elapsed = 1.0f) override;
    //void handleInput(Game& game);

    std::shared_ptr<HealthComponent> getHealth() { return health; }
    std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocity; }
    std::shared_ptr<GraphicsComponent> getGraphicsComponent() override { return graphicsComponent; }
    std::shared_ptr<PlayerStateComponent> getPlayerStateComponent() { return playerState; }

    std::shared_ptr<InputComponent> getInputComponent() override { return input; }

    std::shared_ptr<BoxColliderComponent> getColliderComponent() override { return colliderComponent; }
    std::shared_ptr<PlayerStateComponent> getLogicComponent() { return playerState; }

    bool collidesWith(Entity& other);

    void positionSprite(int row, int col, int spriteWH, float tileScale);

private:
    std::shared_ptr<HealthComponent> health;
    std::shared_ptr<InputComponent> input;
    std::shared_ptr<VelocityComponent> velocity;
    std::shared_ptr<PlayerStateComponent> playerState;
};
